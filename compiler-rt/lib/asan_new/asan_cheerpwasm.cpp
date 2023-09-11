#ifndef ASAN_CHEERPWASM
#define ASAN_CHEERPWASM

#include "asan_internal.h"
#include "asan_mapping.h"
#include "asan_poisoning.h"

#if SANITIZER_CHEERPWASM

#include <cheerpintrin.h>
#include <cassert>

#include <cstdio>

namespace __asan {

void InitializeShadowMemory() {
  // Poison the shadow memory of the shadow area at the start of the address
  // space. This helps catching null pointer dereference.
  uptr size = __builtin_cheerp_grow_memory(0);
  fprintf(stderr, "size: %u\n", (unsigned) size);
  if (size < (kLowShadowEnd * WASM_PAGE_SIZE)) {
          uptr grow_by = (kLowShadowEnd - size) / WASM_PAGE_SIZE;
          fprintf(stderr, "grow_by: %u\n", (unsigned) grow_by);
          fprintf(stderr, "ret: %zu\n", __builtin_cheerp_grow_memory(grow_by));
          fprintf(stderr, "new size: %zu\n",  __builtin_cheerp_grow_memory(0));
  }
  FastPoisonShadow(kLowShadowBeg, kLowShadowEnd - kLowShadowBeg, 0xff);

  // Assert that the shadow region is large enough.  We don't want to start
  // running into the static data region which starts right after the shadow
  // region.
  uptr max_address =
    (__builtin_cheerp_grow_memory(0) * uint64_t(WASM_PAGE_SIZE)) - 1;
  uptr max_shadow_address = MEM_TO_SHADOW(max_address);
  // TODO(sbc): In the growable memory case we should really be checking this
  // every time we grow.
  assert(max_shadow_address <= kLowShadowEnd && "shadow region is too small");
}

} // namespace __asan

#endif // SANITIZER_CHEERPWASM

#endif
