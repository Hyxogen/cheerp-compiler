//===-- sanitizer_emscripten.cc -------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This provides implementations of some functions in sanitizer_linux_libcdep.c
// on emscripten. We are not using sanitizer_linux_libcdep.c because it contains
// a lot of threading and other code that does not work with emscripten yet,
// so instead, some minimal implementations are provided here so that UBSan can
// work.
//===----------------------------------------------------------------------===//

#include "sanitizer_platform.h"
#include "sanitizer_common.h"
#include "sanitizer_stoptheworld.h"

#if SANITIZER_CHEERPWASM

#include <cassert>

namespace __sanitizer {

void ListOfModules::init() {
}

void ListOfModules::fallbackInit() {}

int internal_sigaction(int signum, const void *act, void *oldact) {
        assert(0 && "unsupported");
}

uptr internal_mmap(void *addr, uptr length, int prot, int flags, int fd,
                   u64 offset) {
        assert(0 && "unsupported");
}

uptr internal_munmap(void *addr, uptr length) { assert(0 && "unsupported"); }

void GetThreadStackTopAndBottom(bool at_initialization, uptr *stack_top,
                                uptr *stack_bottom) {
        assert(0 && "unsupported");
}

char *fake_argv[] = {0};
char *fake_envp[] = {0};

char **GetArgv() {
  return fake_argv;
}

char **GetEnviron() {
  return fake_envp;
}

uptr GetTlsSize() {
  return 0;
}

void InitTlsSize() {}

void GetThreadStackAndTls(bool main, uptr *stk_addr, uptr *stk_size,
                          uptr *tls_addr, uptr *tls_size) {
        assert(0 && "unsupported");
}

class SuspendedThreadsListEmscripten final : public SuspendedThreadsList {};

void StopTheWorld(StopTheWorldCallback callback, void *argument) {
        assert(0 && "unsupported");
}

void InitializePlatformCommonFlags(CommonFlags *cf) {}

u64 MonotonicNanoTime() {
        assert(0 && "unsupported");
}

} // namespace __sanitizer

#endif
