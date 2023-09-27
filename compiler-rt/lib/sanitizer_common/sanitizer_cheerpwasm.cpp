#include "sanitizer_cheerpwasm.h"

#if SANITIZER_CHEERPWASM

#include "sanitizer_common.h"
#include "sanitizer_file.h"
#include "sanitizer_cheerpwasm_mmap.h"

#include <cstdio>

namespace __sanitizer {

uptr ReadBinaryName(/*out*/char *buf, uptr buf_len) {
  const char *default_binary_name = "default.binary.name";
  const size_t len = strlen(default_binary_name);
  size_t n = buf_len < len ? buf_len : len;
  REAL(memcpy)(buf, default_binary_name, n);
  return n;
}

uptr ReadLongProcessName(/*out*/ char *buf, uptr buf_len) {
  return ReadBinaryName(buf, buf_len);
}

const char *GetEnv(const char *name) {
  (void) name;
  // CHEERPASAN: TODO implement
  return nullptr;  // Not found.
}

uptr GetPageSize() {
  return 64*1024;//TODO make define
}

tid_t GetTid() {
  return 1;
}

void ReportFile::Write(const char *buffer, uptr length) {
  // CHEERPASAN: TODO do not hardcode output stream
  fwrite(buffer, sizeof *buffer, length, stderr);
}

uptr MapDynamicShadow(uptr shadow_size_bytes, uptr shadow_scale,
                      uptr min_shadow_base_alignment,
                      UNUSED uptr &high_mem_end) {
  const uptr granularity = GetMmapGranularity();
  const uptr alignment =
      Max<uptr>(granularity << shadow_scale, 1ULL << min_shadow_base_alignment);
  const uptr left_padding =
      Max<uptr>(granularity, 1ULL << min_shadow_base_alignment);

  const uptr shadow_size = RoundUpTo(shadow_size_bytes, granularity);
  const uptr map_size = shadow_size + left_padding + alignment;

  const uptr map_start = (uptr)MmapNoAccess(map_size);
  CHECK_NE(map_start, ~(uptr)0);

  const uptr shadow_start = RoundUpTo(map_start + left_padding, alignment);

  UnmapFromTo(map_start, shadow_start - left_padding);
  UnmapFromTo(shadow_start + shadow_size, map_start + map_size);

  return shadow_start;
}

// Reserve memory range [beg, end].
// We need to use inclusive range because end+1 may not be representable.
void ReserveShadowMemoryRange(uptr beg, uptr end, const char *name,
                              bool madvise_shadow) {
  CHECK_EQ((beg % GetMmapGranularity()), 0);
  CHECK_EQ(((end + 1) % GetMmapGranularity()), 0);
  uptr size = end - beg + 1;
  DecreaseTotalMmap(size);  // Don't count the shadow against mmap_limit_mb.
  if (!MmapFixedNoReserve(beg, size, name)) {
    Report(
        "ReserveShadowMemoryRange failed while trying to map 0x%zx bytes. "
        "Perhaps you're using ulimit -v\n",
        size);
    Abort();
  }
}

void InitializePlatformCommonFlags(CommonFlags *cf) {}
void InitializePlatformEarly() {}
void CheckASLR() {}
void DisableCoreDumperIfNecessary() {}
void InstallDeadlySignalHandlers(void (*)(int, void*, void*)) {}
void InitializeCoverage(bool, char const*) {}
void InitTlsSize() {}
uptr internal_getpid() { return 1; }

void GetThreadStackAndTls(bool main, uptr *stk_addr, uptr *stk_size,
                          uptr *tls_addr, uptr *tls_size) {}
void SetAlternateSignalStack() {}

} // namespace __sanitizer

#endif // SANITIZER_CHEERPWASM
