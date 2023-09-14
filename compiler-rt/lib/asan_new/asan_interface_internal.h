//===-- asan_interface_internal.h -------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// This header declares the AddressSanitizer runtime interface functions.
// The runtime library has to define these functions so the instrumented program
// could call them.
//
// See also include/sanitizer/asan_interface.h
//===----------------------------------------------------------------------===//
#ifndef ASAN_INTERFACE_INTERNAL_H
#define ASAN_INTERFACE_INTERNAL_H

#include "sanitizer_common/sanitizer_internal_defs.h"

using __sanitizer::u32;
using __sanitizer::u64;
using __sanitizer::uptr;

extern "C" {
// This function should be called at the very beginning of the process,
// before any instrumented code is executed and before any call to malloc.
SANITIZER_INTERFACE_ATTRIBUTE void __asan_init();
SANITIZER_INTERFACE_ATTRIBUTE void __asan_version_mismatch_check_v8();

// This structure describes an instrumented global variable.
struct __asan_global {
  uptr beg;                // The address of the global.
  uptr size;               // The original size of the global.
  uptr size_with_redzone;  // The size with the redzone.
  const char *name;        // Name as a C string.
  const char *module_name; // Module name as a C string. This pointer is a
                           // unique identifier of a module.
  uptr has_dynamic_init;   // Non-zero if the global has dynamic initializer.
  uptr windows_padding;    // TODO: Figure out how to remove this padding
                           // that's simply here to make the MSVC incremental
                           // linker happy...
  uptr odr_indicator;      // The address of the ODR indicator symbol.
};

extern uptr __asan_shadow_memory_dynamic_address;
}
#endif
