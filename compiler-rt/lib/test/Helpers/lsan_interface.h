//===-- sanitizer/lsan_interface.h ------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of LeakSanitizer.
//
// Public interface header.
//===----------------------------------------------------------------------===//
#ifndef SANITIZER_LSAN_INTERFACE_H
#define SANITIZER_LSAN_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

// Check for leaks now. This function behaves identically to the default
// end-of-process leak check. In particular, it will terminate the process if
// leaks are found and the exitcode runtime flag is non-zero.
// Subsequent calls to this function will have no effect and end-of-process
// leak check will not run. Effectively, end-of-process leak check is moved to
// the time of first invocation of this function.
// By calling this function early during process shutdown, you can instruct
// LSan to ignore shutdown-only leaks which happen later on.
void __lsan_do_leak_check(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SANITIZER_LSAN_INTERFACE_H
