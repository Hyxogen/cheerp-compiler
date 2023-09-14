//===-- asan_internal.h -----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// ASan-private header which defines various general utilities.
//===----------------------------------------------------------------------===//
#ifndef ASAN_INTERNAL
#define ASAN_INTERNAL

#include "asan_interface_internal.h"
#include "sanitizer_common_new/sanitizer_internal_defs.h"

#if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#  error \
      "The AddressSanitizer run-time should not be instrumented by AddressSanitizer"
#endif

namespace __asan {

// asan_shadow_setup.cpp
void InitializeShadowMemory();

} // namespace __asan

#endif
