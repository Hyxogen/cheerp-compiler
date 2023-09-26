#include "sanitizer_cheerpwasm_mmap.h"

#if SANITIZER_CHEERPWASM
#include <cheerpintrin.h>
#include <cstdint>
#include <cerrno>
#include "sanitizer_common.h"
#include <sys/mman.h>

#include <cstdio>

extern uint32_t _heapStart;
extern uint32_t _heapEnd;
//extern uint32_t _maxAddress;
uint32_t _maxAddress = _heapEnd; //TODO fix this properly, this is a hack

namespace __sanitizer {

#define WASM_PAGESIZE (64*1024)
#define WASM_MAX_PAGES (65536)
//#define MMAP_PAGESIZE 4096
//#define MMAP_PAGECOUNT (WASM_PAGESIZE*WASM_MAX_PAGES)/MMAP_PAGESIZE

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

static Page pages[WASM_MAX_PAGES];
static uptr max_page_count = 0;

static uptr PageCount() {
  return sizeof(pages) / sizeof(pages[0]);
}

static uptr FindPages(uptr start, uptr page_count) {
  CHECK_LT(start, page_count);

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

  uptr end = page + (len / WASM_PAGESIZE);
  for (uptr idx = page; page < end; ++ idx) {
    pages[idx].MakeFree();
  }

  if (len % WASM_PAGESIZE) {
    pages[end].FreeStarting(static_cast<uint16_t>(len % WASM_PAGESIZE));
  }
}

uptr InternalMmap(uptr addr, uptr len, int prot, int flags, int fildes) {
  CHECK_EQ(0, addr % WASM_PAGESIZE);

  if (len % WASM_PAGESIZE) {
    len += WASM_PAGESIZE - (len % WASM_PAGESIZE);
  }
  CHECK_EQ(0, len % WASM_PAGESIZE);

  uptr page_count = len / WASM_PAGESIZE;

  if (!(flags & (MAP_ANON | MAP_ANONYMOUS))) {
    errno = EINVAL;
    return -1;
  }

  uptr page = FindPages(addr / WASM_PAGESIZE, page_count);
  if (page == -1) {
    errno = ENOMEM;
    return -1;
  }

  ReservePages(page, page_count);
  return page;
}

void InternalMunmap(uptr addr, uptr len) {
  CHECK_EQ(0, addr % WASM_PAGESIZE);
  FreePages(addr / WASM_PAGESIZE, len);
}

//TODO add a check variable if initialized
void SetupMemoryMapping() {
  size_t used = __builtin_cheerp_grow_memory(0);
  max_page_count = _maxAddress / WASM_PAGESIZE;
  printf("maxAddress %u, max_page_count: %zu\n", _maxAddress, max_page_count);

  for (uptr idx = 0; idx < PageCount(); ++idx) {
    pages[idx].MakeFree();
  }

  if (used < max_page_count) {
    unsigned int ret = __builtin_cheerp_grow_memory(max_page_count - used);
    if (ret == -1) {
      abort();//If this is failing, you're not running with enough memory
    }
  }

  ReservePages(0, used);// use _heapStart instead of __buitin_cheerp_grow_memory(0) for how many pages are already used
}

void *MmapOrDie(uptr size, const char *mem_type, bool raw_report) {
  size = RoundUpTo(size, GetPageSizeCached());
  printf("%s\n", mem_type);
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
  range_start = RoundDownTo(range_start, WASM_PAGESIZE);
  range_end = RoundUpTo(range_start, WASM_PAGESIZE);
  return IsFree(range_start, range_end);
}

} //namespace __sanitizer

#endif // SANITIZER_CHEERPWASM
