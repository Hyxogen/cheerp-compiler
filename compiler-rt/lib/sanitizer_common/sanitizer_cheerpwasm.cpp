#include "sanitizer_cheerpwasm.h"

#if SANITIZER_CHEERPWASM

#  include <stdlib.h>

#  include "sanitizer_cheerpwasm_mmap.h"
#  include "sanitizer_common.h"
#  include "sanitizer_file.h"

__attribute__((cheerp_asmjs)) char *volatile _stackBottom = (char *)0xdeadbeef;
__attribute__((cheerp_asmjs)) char *volatile _stackTop = (char *)0xdeadbeef;

namespace __sanitizer {

void ListOfModules::init() {
  modules_.Initialize(2);

  LoadedModule main_module;
  main_module.set("main", 0);

  // Cheerp represents program counters as offsets into WebAssembly
  // modules. For JavaScript code, the "program counter" is the line number
  // of the JavaScript code with the high bit set.
  // Therefore, PC values 0x80000000 and beyond represents JavaScript code.
  // As a result, 0x00000000 to 0x7FFFFFFF represents PC values for WASM code.
  // We consider WASM code as main_module.
  main_module.addAddressRange(0, 0x7FFFFFFF, /*executable*/ true,
                              /*writable*/ false);
  modules_.push_back(main_module);

  // The remaining PC values, 0x80000000 to 0xFFFFFFFF, are JavaScript,
  // and we consider it a separate module, js_module.
  LoadedModule js_module;
  js_module.set("JavaScript", 0x80000000);
  js_module.addAddressRange(0x80000000, 0xFFFFFFFF, /*executable*/ true,
                            /*writable*/ false);
  modules_.push_back(js_module);
}

int Atexit(void (*function)(void)) { return atexit(function); }

void ListOfModules::fallbackInit() { clear(); }

uptr ReadBinaryName(/*out*/ char *buf, uptr buf_len) {
  const char *default_binary_name = "default.binary.name";
  const size_t len = internal_strlen(default_binary_name);
  size_t n = buf_len < len ? buf_len : len;
  internal_memcpy(buf, default_binary_name, n);
  return n;
}

uptr ReadLongProcessName(/*out*/ char *buf, uptr buf_len) {
  return ReadBinaryName(buf, buf_len);
}

const char *GetEnv(const char *name) { return getenv(name); }

uptr GetPageSize() { return GetMmapGranularity(); }

tid_t GetTid() { return 0; }

uptr GetThreadSelf() { return 0; }
bool SupportsColoredOutput(fd_t fd) { return false; }

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

void InitializePlatformCommonFlags(CommonFlags *cf) {}
void InitializePlatformEarly() {}
void CheckASLR() {}
void DisableCoreDumperIfNecessary() {}
void InstallDeadlySignalHandlers(void (*)(int, void *, void *)) {}
void InitializeCoverage(bool, char const *) {}
void InitTlsSize() {}
uptr internal_getpid() { return 1; }

void GetThreadStackAndTls(bool main, uptr *stk_addr, uptr *stk_size,
                          uptr *tls_addr, uptr *tls_size) {
  *stk_addr = (uptr)_stackTop;
  *stk_size = _stackBottom - _stackTop;
}

void SetAlternateSignalStack() {}

void internal__exit(int exitcode) { exit(exitcode); }

}  // namespace __sanitizer

#endif  // SANITIZER_CHEERPWASM
