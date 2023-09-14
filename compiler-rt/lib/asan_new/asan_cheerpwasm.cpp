#ifndef ASAN_CHEERPWASM
#define ASAN_CHEERPWASM

#include "asan_internal.h"
#include "asan_interface_internal.h"
#include "asan_mapping.h"
#include "asan_poisoning.h"

#if SANITIZER_CHEERPWASM

#include <cheerpintrin.h>
#include <cassert>
#include <cstdlib>

#include <cstdio>

#define WASM_PAGE_SIZE (64*1024)

namespace __asan {
void InitializeShadowMemory() {
        //TODO allocate shadow memory based on the upper limit used during compilation
        //TODO set highMemEnd midMemEnd etc. in __asan_init
        
        size_t allocated_pages = __builtin_cheerp_grow_memory(0);
        size_t needed_pages = (kLowShadowEnd  + (WASM_PAGE_SIZE - 1)) / WASM_PAGE_SIZE;

        if (allocated_pages < needed_pages) {
                size_t ret = __builtin_cheerp_grow_memory(needed_pages - allocated_pages);
                assert(ret != -1);
        }

        //FastPoisonShadow(kLowShadowBeg, kLowShadowEnd - kLowShadowBeg, 0xff);
        memset((void*) kLowShadowBeg, 0xff, kLowShadowEnd - kLowShadowBeg);

        void* low_beg = (void*) kLowShadowBeg;
        void* null_shadow = (void*) MEM_TO_SHADOW(0);
        char null_shadow_val = *(char*) null_shadow;
        fprintf(stderr, "lowShadowBeg: %p, null_shadow: %p, null_shadow_val: %hhx\n", low_beg, null_shadow, null_shadow_val);
}

} // namespace __asan

#endif // SANITIZER_CHEERPWASM

#endif
