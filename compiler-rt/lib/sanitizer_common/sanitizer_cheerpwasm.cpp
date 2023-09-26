#include "sanitizer_cheerpwasm.h"

#if SANITIZER_CHEERPWASM

#include "sanitizer_common.h"
#include "sanitizer_file.h"

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

void InitializePlatformCommonFlags(CommonFlags *cf) {}
void InitializePlatformEarly() {}
void CheckASLR() {}
void DisableCoreDumperIfNecessary() {}
void InstallDeadlySignalHandlers(void (*)(int, void*, void*)) {}
void InitializeCoverage(bool, char const*) {}
void InitTlsSize() {}

} // namespace __sanitizer

#endif // SANITIZER_CHEERPWASM
