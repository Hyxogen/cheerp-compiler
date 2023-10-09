// Test needle overflow in strcasestr function
// RUN: %clang_asan %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clang_asan -cheerp-linear-output=asmjs %s -o %t && not %run %t 2>&1 | FileCheck %s

#define _GNU_SOURCE
#include <assert.h>
#include <string.h>
#include "Helpers/asan_interface.h"

int main(int argc, char **argv) {
  char *r = 0;
  char s1[] = "ab";
  char s2[4] = "cba";
  __asan_poison_memory_region ((char *)&s2[2], 2);
  r = strcasestr(s1, s2);
  assert(r == 0);
  // CHECK:'s2'{{.*}} <== Memory access at offset {{[0-9]+}} partially overflows this variable
  return 0;
}
