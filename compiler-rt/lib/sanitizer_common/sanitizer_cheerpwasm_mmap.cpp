#include "sanitizer_cheerpwasm_mmap.h"

#if SANITIZER_CHEERPWASM
#include <cheerpintrin.h>
#include <cstdint>
#include <cerrno>
#include "sanitizer_common.h"
#include <sys/mman.h>

#include <cstdio>

extern "C" {
extern char* volatile _heapStart;
extern char* volatile _heapEnd;
__attribute__((cheerp_asmjs)) char* volatile _maxAddress = (char*)0xdeadbeef;
}

namespace __sanitizer {

//TODO make mmap pages smaller
//#define WASM_PAGESIZE (64*1024)
//#define WASM_MAX_PAGES (65536)
//#define MMAP_PAGESIZE 4096
//#define MMAP_PAGECOUNT (WASM_PAGESIZE*WASM_MAX_PAGES)/MMAP_PAGESIZE
constexpr static uptr WASM_PAGESIZE = 64 * 1024;
constexpr static uptr WASM_MAX_PAGES = 65536;
constexpr static uptr MMAP_PAGESIZE = 4096;
constexpr static uptr MMAP_PAGECOUNT = ((uptr) -1)/MMAP_PAGESIZE;

struct Page {
private:
  constexpr static uint16_t FREE_PAGE = -1;
  constexpr static uint16_t FULLY_USED_PAGE = 0;
public:
  uint16_t _start = FREE_PAGE;

  bool IsUsed() const {
    return _start != FREE_PAGE;
  }

  bool IsFree() const {
    return !IsUsed();
  }

  void MakeUsed() {
    _start = FULLY_USED_PAGE;
  }

  void MakeFree() {
    _start = FREE_PAGE;
  }

  void FreeStarting(uint16_t n) {
    _start = n;
  }
};

static Page pages[MMAP_PAGECOUNT];
static uptr max_page_count = 0;

static uptr PageCount() {
  return sizeof(pages) / sizeof(pages[0]);
}

static uptr FindPages(uptr start, uptr page_count) {
  CHECK_LT(start, PageCount());

  uptr best = -1;
  uptr best_len = 0;

  for (uptr idx = start; idx < PageCount(); ++idx) {
    Page& page = pages[idx];

    if (page.IsFree()) {
      if (!best_len)
        best = idx;
      ++best_len;
    } else {
      best_len = 0;
    }

    if (best_len == page_count)
      return best;
  }

  if (start)
    return FindPages(0, page_count);
  return -1;
}

static bool IsFree(uptr page, uptr page_count) {
  uptr end = page + page_count;
  for (uptr idx = page;  idx < end; ++idx) {
    if (pages[idx].IsUsed())
      return false;
  }
  return true;
}

static void ReservePages(uptr page, uptr page_count) {
  CHECK_LT(page, PageCount());

  uptr end = page + page_count;
  for (uptr idx = page; idx < end; ++idx) {
    pages[idx].MakeUsed();
  }
}

static void FreePages(uptr page, uptr len) {
  CHECK_LT(page, PageCount());

  uptr end = page + (len / MMAP_PAGESIZE);
  for (uptr idx = page; idx < end; ++ idx) {
    pages[idx].MakeFree();
  }

  if (len % MMAP_PAGESIZE) {
    pages[end].FreeStarting(static_cast<uint16_t>(len % MMAP_PAGESIZE));
  }
}

DECLARE_REAL(void*, memset, void*, int, size_t)

uptr InternalMmap(uptr addr, uptr len, int prot, int flags, int fildes) {
  CHECK_EQ(0, addr % MMAP_PAGESIZE);

  if (len % MMAP_PAGESIZE) {
    len += MMAP_PAGESIZE - (len % MMAP_PAGESIZE);
  }
  CHECK_EQ(0, len % MMAP_PAGESIZE);

  uptr page_count = len / MMAP_PAGESIZE;

  if (!(flags & (MAP_ANON | MAP_ANONYMOUS))) {
    errno = EINVAL;
    return -1;
  }

  uptr page = addr / MMAP_PAGESIZE;
  if (!(flags & MAP_FIXED)) {
    page = FindPages(addr / MMAP_PAGESIZE, page_count);
  }

  if (page == -1) {
    errno = ENOMEM;
    return -1;
  }

  ReservePages(page, page_count);
  uptr res = page * MMAP_PAGESIZE;
  REAL(memset)(reinterpret_cast<void*>(res), 0, len);
  return res;
}

void InternalMunmap(uptr addr, uptr len) {
  CHECK_EQ(0, addr % MMAP_PAGESIZE);
  FreePages(addr / MMAP_PAGESIZE, len);
}

//TODO add a check if trying to mmap without having it initialized here
void SetupMemoryMapping() {
  max_page_count = reinterpret_cast<uptr>(_maxAddress) / WASM_PAGESIZE;
  int used = __builtin_cheerp_grow_memory(0);
  if (used == -1) {
    used = max_page_count;// assume that all memory is already reserved and hope for the best
  }

  for (uptr idx = 0; idx < PageCount(); ++idx) {
    pages[idx].MakeFree();
  }

  if (used < max_page_count) {
    unsigned int ret = __builtin_cheerp_grow_memory(max_page_count - used);
    if (ret == -1) {
      abort();//If this is failing, you're not running with enough memory
    }
  }

  uptr i = (reinterpret_cast<uptr>(_heapStart) + (MMAP_PAGESIZE -1)) / MMAP_PAGESIZE;
  //uptr i = ((used * WASM_PAGESIZE) + (MMAP_PAGESIZE - 1))  / MMAP_PAGESIZE;
  /*printf(
      "unrounded %zu, already using %u pages, heapStart: %p, internal: %zu\n",
      used, i, (void*) _heapStart, sizeof(pages));*/
  ReservePages(0, i);// use _heapStart instead of __buitin_cheerp_grow_memory(0) for how many pages are already used
}

uptr GetMaxUserVirtualAddress() {
  return ~(uptr) 0;
}

void *MmapOrDie(uptr size, const char *mem_type, bool raw_report) {
  size = RoundUpTo(size, GetPageSizeCached());
  uptr res =
      InternalMmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1);
  if (UNLIKELY(res == -1))
    ReportMmapFailureAndDie(size, mem_type, "allocate", errno, raw_report);
  IncreaseTotalMmap(size);
  return (void *)res;
}

void UnmapOrDie(void *addr, uptr size) {
  InternalMunmap(reinterpret_cast<uptr>(addr), size);
  DecreaseTotalMmap(size);
}

bool MemoryRangeIsAvailable(uptr range_start, uptr range_end) {
  range_start = RoundDownTo(range_start, MMAP_PAGESIZE);
  range_end = RoundUpTo(range_start, MMAP_PAGESIZE);
  return IsFree(range_start, range_end);
}

uptr GetMmapGranularity() {
  return MMAP_PAGESIZE;
}

void UnmapFromTo(uptr from, uptr to) {
  if (to == from)
    return;
  CHECK(to >= from);
  InternalMunmap(from, to - from);
}

//Doesn't actually protect memory on cheerp
void *MmapNoAccess(uptr size) {
  unsigned flags = MAP_PRIVATE | MAP_ANON | MAP_NORESERVE;
  return (void *)InternalMmap(0, size, PROT_NONE, flags, -1);
}

static bool MmapFixed(uptr fixed_addr, uptr size, int additional_flags,
                      const char *name) {
  size = RoundUpTo(size, GetPageSizeCached());
  fixed_addr = RoundDownTo(fixed_addr, GetPageSizeCached());
  uptr p =
      InternalMmap(fixed_addr, size, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_FIXED | additional_flags | MAP_ANON, -1);
  int reserrno = errno;
  if (p == -1) {
    Report(
        "ERROR: %s failed to "
        "allocate 0x%zx (%zd) bytes at address %zx (errno: %d)\n",
        SanitizerToolName, size, size, fixed_addr, reserrno);
    return false;
  }
  IncreaseTotalMmap(size);
  return true;
}

bool MmapFixedNoReserve(uptr fixed_addr, uptr size, const char *name) {
  return MmapFixed(fixed_addr, size, MAP_NORESERVE, name);
}

void *MmapOrDieOnFatalError(uptr size, const char *mem_type) {
  size = RoundUpTo(size, GetPageSizeCached());
  uptr res = InternalMmap(0, size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANON, -1);
  int reserrno = errno;
  if (UNLIKELY(res == -1)) {
    if (reserrno == ENOMEM)
      return nullptr;
    ReportMmapFailureAndDie(size, mem_type, "allocate", reserrno);
  }
  IncreaseTotalMmap(size);
  return (void *)res;
}

// We want to map a chunk of address space aligned to 'alignment'.
// We do it by mapping a bit more and then unmapping redundant pieces.
// We probably can do it with fewer syscalls in some OS-dependent way.
void *MmapAlignedOrDieOnFatalError(uptr size, uptr alignment,
                                   const char *mem_type) {
  CHECK(IsPowerOfTwo(size));
  CHECK(IsPowerOfTwo(alignment));
  uptr map_size = size + alignment;
  uptr map_res = (uptr)MmapOrDieOnFatalError(map_size, mem_type);
  if (UNLIKELY(!map_res))
    return nullptr;
  uptr map_end = map_res + map_size;
  uptr res = map_res;
  if (!IsAligned(res, alignment)) {
    res = (map_res + alignment - 1) & ~(alignment - 1);
    UnmapOrDie((void*)map_res, res - map_res);
  }
  uptr end = res + size;
  end = RoundUpTo(end, GetPageSizeCached());
  if (end != map_end)
    UnmapOrDie((void*)end, map_end - end);
  return (void*)res;
}

void *MmapNoReserveOrDie(uptr size, const char *mem_type) {
  size = RoundUpTo(size, GetPageSizeCached());
  uptr p = InternalMmap(0, size, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANON | MAP_NORESERVE, -1);
  int reserrno = errno;
  if (UNLIKELY(p == -1))
    ReportMmapFailureAndDie(size, mem_type, "allocate noreserve", reserrno);
  IncreaseTotalMmap(size);
  return (void *)p;
}

} //namespace __sanitizer

#endif // SANITIZER_CHEERPWASM
