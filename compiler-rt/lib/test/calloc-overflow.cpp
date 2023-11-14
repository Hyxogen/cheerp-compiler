// RUN: %clangxx_asan -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -cheerp-linear-output=asmjs -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s

#include <stdio.h>
#include <stdlib.h>

int main() {
  void *volatile p = calloc(-1, 1000);
  // CHECK: {{ERROR: AddressSanitizer: calloc parameters overflow: count \* size \(.* \* 1000\) cannot be represented in type size_t}}
  // DONTCHECK: {{#0 0x.* in .*calloc}}
  // DONTCHECK: {{#1 0x.* in main .*calloc-overflow.cpp:}}[[@LINE-3]]
  // CHECK: SUMMARY: AddressSanitizer: calloc-overflow

  //printf("calloc returned: %zu\n", (size_t)p);
  // DONTCHECK-NULL: calloc returned: 0

  return 0;
}
