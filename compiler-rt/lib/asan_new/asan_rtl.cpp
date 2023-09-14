//===-- asan_rtl.cpp ------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// Main file of the ASan run-time library.
//===----------------------------------------------------------------------===//
#include "asan_internal.h"
#include "asan_poisoning.h"
#include "asan_report.h"
#include "asan_interface_internal.h"

#include <cstdio>
#include <cstdint>

extern uintptr_t _heapStart;
extern uintptr_t _heapEnd;

int __asan_option_detect_stack_use_after_return;  // Global interface symbol.
uptr __asan_shadow_memory_dynamic_address;

namespace __asan {

int asan_inited = 0;
uptr kHighMemEnd, kMidMemBeg, kMidMemEnd;
// -------------------------- Run-time entry ------------------- {{{1
// exported functions
#define ASAN_REPORT_ERROR(type, is_write, size)                                \
  extern "C" NOINLINE INTERFACE_ATTRIBUTE void __asan_report_##type##size(     \
      uptr addr) {                                                             \
    /*GET_CALLER_PC_BP_SP;*/                                                   \
    ReportGenericError(0, 0, 0, addr, is_write, size, 0, true);                \
  }                                                                            \
  extern "C" NOINLINE INTERFACE_ATTRIBUTE void __asan_report_exp_##type##size( \
      uptr addr, u32 exp) {                                                    \
    /*GET_CALLER_PC_BP_SP;*/                                                   \
    ReportGenericError(0, 0, 0, addr, is_write, size, exp, true);              \
  }                                                                            \
  extern "C" NOINLINE INTERFACE_ATTRIBUTE void                                 \
      __asan_report_##type##size##_noabort(uptr addr) {                        \
    /*GET_CALLER_PC_BP_SP;*/                                                   \
    ReportGenericError(0, 0, 0, addr, is_write, size, 0, false);               \
  }

ASAN_REPORT_ERROR(load, false, 1)
ASAN_REPORT_ERROR(load, false, 2)
ASAN_REPORT_ERROR(load, false, 4)
ASAN_REPORT_ERROR(load, false, 8)
ASAN_REPORT_ERROR(load, false, 16)
ASAN_REPORT_ERROR(store, true, 1)
ASAN_REPORT_ERROR(store, true, 2)
ASAN_REPORT_ERROR(store, true, 4)
ASAN_REPORT_ERROR(store, true, 8)
ASAN_REPORT_ERROR(store, true, 16)

static void AsanInitInternal() {
  if (LIKELY(asan_inited)) return;
  //SanitizerToolName = "AddressSanitizer";
  //
  kHighMemEnd = ~(uptr)0;
  kMidMemBeg = kMidMemEnd = 0;

  __asan_shadow_memory_dynamic_address = (uptr) _heapStart;
  fprintf(stderr,
          "__asan_shadow_memory_dynamic_address: %p, _heapStart: %p, _heapEnd: "
          "%p\n",
          (void*) __asan_shadow_memory_dynamic_address, (void *)_heapStart,
          (void *)_heapEnd);
  __asan_option_detect_stack_use_after_return = 0;
  InitializeShadowMemory();

  asan_inited = 1;
}
} // namespace __asan

using namespace __asan;

void __asan_init() {
  //AsanActivate();
  AsanInitInternal();
}

void __asan_version_mismatch_check_v8() {
}
