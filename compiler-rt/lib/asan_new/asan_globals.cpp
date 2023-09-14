//===-- asan_globals.cpp --------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// Handle globals.
//===----------------------------------------------------------------------===//

#include "asan_internal.h"
#include "asan_mapping.h"
#include "asan_poisoning.h"

namespace __asan {

void __asan_register_globals(void *globals, uptr n) {}
void __asan_unregister_globals(void *globals, uptr n) {}

} // namespace __asan
