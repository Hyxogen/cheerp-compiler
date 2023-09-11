//===-- asan_report.h -------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// ASan-private header for error reporting functions.
//===----------------------------------------------------------------------===//

#ifndef ASAN_REPORT_H
#define ASAN_REPORT_H

#include "asan_internal.h"

namespace __asan {
void ReportGenericError(uptr pc, uptr bp, uptr sp, uptr addr, bool is_write,
                        uptr access_size, u32 exp, bool fatal);
} // namespace __asan

#endif
