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

  /*
void InitializeShadowMemory() {
  // CHEERPASAN: TODO allocate shadow memory based on the upper limit used during
  // compilation
  // CHEERPASAN: TODO set highMemEnd midMemEnd etc. in __asan_init

  size_t allocated_pages = __builtin_cheerp_grow_memory(0);
  size_t needed_pages = (kLowShadowEnd + (WASM_PAGE_SIZE - 1)) / WASM_PAGE_SIZE;

  if (allocated_pages < needed_pages) {
    size_t ret = __builtin_cheerp_grow_memory(needed_pages - allocated_pages);
    assert(ret != -1);
  }

  FastPoisonShadow(kLowShadowBeg, kLowShadowEnd - kLowShadowBeg, 0xff);
  //memset((void *)kLowShadowBeg, 0xff, kLowShadowEnd - kLowShadowBeg);

  void *low_beg = (void *)kLowShadowBeg;
  void *null_shadow = (void *)MEM_TO_SHADOW(0);
  char null_shadow_val = *(char *)null_shadow;
}*/

void AsanCheckDynamicRTPrereqs() {}
void AsanCheckIncompatibleRT() {}
void InitializePlatformInterceptors() {}
void InitializePlatformExceptionHandlers() {}
bool IsSystemHeapAddress (uptr addr) { return false; }
void ReplaceSystemMalloc() {}
void AsanTSDInit(void (*)(void*)) {}

void *AsanDoesNotSupportStaticLinkage() {
  // On Linux, this is some magic that fails linking with -static.
  // On Emscripten, we have to do static linking, so we stub this out.
  return nullptr;
}

void InitializeAsanInterceptors() {}

void FlushUnneededASanShadowMemory(uptr p, uptr size) {}

} // namespace __asan

#endif // SANITIZER_EMSCRIPTEN


