// Test for the leak_check_at_exit flag.
// RUN: %clangxx_asan %s -o %t && not %run %t foo 2>&1 | FileCheck %s --check-prefix=CHECK-do
// RUN: %clangxx_asan -cheerp-linear-output=asmjs %s -o %t && not %run %t foo 2>&1 | FileCheck %s --check-prefix=CHECK-do
//
#include <stdio.h>
#include <stdlib.h>
#include "Helpers/lsan_interface.h"

int main(int argc, char *argv[]) {
  argc += 2;
  fprintf(stderr, "Test alloc: %p.\n", malloc(1337));
  if (argc > 1)
    __lsan_do_leak_check();
  return 0;
}

// CHECK-do: SUMMARY: {{(Leak|Address)}}Sanitizer:
// CHECK-dont-NOT: SUMMARY: {{(Leak|Address)}}Sanitizer:
