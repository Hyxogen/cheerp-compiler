//===-- asan_poisoning.h ----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// Shadow memory poisoning by ASan RTL and by user application.
//===----------------------------------------------------------------------===//

#include "asan_mapping.h"
#include "asan_new/asan_internal.h"

#include <cstring>

namespace __asan {

// Fast versions of PoisonShadow and PoisonShadowPartialRightRedzone that
// assume that memory addresses are properly aligned. Use in
// performance-critical code with care.
ALWAYS_INLINE void FastPoisonShadow(uptr aligned_beg, uptr aligned_size,
                                    u8 value) {
  uptr shadow_beg = MEM_TO_SHADOW(aligned_beg);
  uptr shadow_end =
      MEM_TO_SHADOW(aligned_beg + aligned_size - ASAN_SHADOW_GRANULARITY) + 1;
  memset((void *)shadow_beg, value, shadow_end - shadow_beg);
  }
} // namespace __asan
