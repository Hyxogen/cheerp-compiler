#include "asan_interceptors.h"
#include "asan_internal.h"
#include "asan_mapping.h"
#include "asan_poisoning.h"
#include "asan_stack.h"
#include "asan_thread.h"

#if SANITIZER_CHEERPWASM
#include <cheerpintrin.h>
#include <cassert>
#include <cstdlib>

#include <cstdio>

#define WASM_PAGE_SIZE (64*1024)
#define __ATTRP_C11_THREAD ((void*)(uptr)-1)

namespace __asan {

uptr FindDynamicShadowStart() {
  uptr shadow_size_bytes = MemToShadowSize(kHighMemEnd);
  return MapDynamicShadow(shadow_size_bytes, ASAN_SHADOW_SCALE,
                          /*min_shadow_base_alignment*/ 0, kHighMemEnd);
}

void AsanCheckDynamicRTPrereqs() {}
void AsanCheckIncompatibleRT() {}
void InitializePlatformInterceptors() {}
void InitializePlatformExceptionHandlers() {}
bool IsSystemHeapAddress (uptr addr) { return false; }
void ReplaceSystemMalloc() {}

void *AsanDoesNotSupportStaticLinkage() {
  // On Linux, this is some magic that fails linking with -static.
  // On Emscripten, we have to do static linking, so we stub this out.
  return nullptr;
}

void InitializeAsanInterceptors() {}

void FlushUnneededASanShadowMemory(uptr p, uptr size) {}

static void (*tsd_destructor)(void *tsd) = nullptr;

struct tsd_key {
  // tsd_key() : key(nullptr) {} can't use this, since it will try to initialize
  // itself in cxx_global_var_init after __asan_init exited
  ~tsd_key() {
    CHECK(tsd_destructor);
    if (key)
      (*tsd_destructor)(key);
  }
  void *key = nullptr;
};

static /*thread_local*/ struct tsd_key key;

void AsanTSDInit(void (*destructor)(void *tsd)) {
  CHECK(!tsd_destructor);
  tsd_destructor = destructor;
}

void *AsanTSDGet() {
  CHECK(tsd_destructor);
  return key.key;
}

void AsanTSDSet(void *tsd) {
  CHECK(tsd_destructor);
  CHECK(tsd);
  CHECK(!key.key);
  key.key = tsd;
}

void PlatformTSDDtor(void *tsd) {
  CHECK(tsd_destructor);
  CHECK_EQ(key.key, tsd);
  key.key = nullptr;
  // Make sure that signal handler can not see a stale current thread pointer.
  atomic_signal_fence(memory_order_seq_cst);
  AsanThread::TSDDtor(tsd);
}

} // namespace __asan

#endif // SANITIZER_EMSCRIPTEN


