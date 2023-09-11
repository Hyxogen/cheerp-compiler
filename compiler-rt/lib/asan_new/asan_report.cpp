//===-- asan_report.cpp ---------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// This file contains error reporting code.
//===----------------------------------------------------------------------===//

#include "asan_report.h"

#include <cstdlib>
#include <cstdio>

namespace __asan {
void ReportGenericError(uptr pc, uptr bp, uptr sp, uptr addr, bool is_write,
                        uptr access_size, u32 exp, bool fatal) {
  /*if (__asan_test_only_reported_buggy_pointer) {
    *__asan_test_only_reported_buggy_pointer = addr;
    return;
  }
  if (!fatal && SuppressErrorReport(pc)) return;
  ENABLE_FRAME_POINTER;

  // Optimization experiments.
  // The experiments can be used to evaluate potential optimizations that remove
  // instrumentation (assess false negatives). Instead of completely removing
  // some instrumentation, compiler can emit special calls into runtime
  // (e.g. __asan_report_exp_load1 instead of __asan_report_load1) and pass
  // mask of experiments (exp).
  // The reaction to a non-zero value of exp is to be defined.
  (void)exp;

  ScopedInErrorReport in_report(fatal);
  ErrorGeneric error(GetCurrentTidOrInvalid(), pc, bp, sp, addr, is_write,
                     access_size);
  in_report.ReportError(error);*/
  fprintf(stderr, "error at %p, is_write: %d, size: %u\n", (void *)addr,
          (int)is_write, (unsigned)access_size);
  if (fatal)
    abort();
}
} // namespace __asan
