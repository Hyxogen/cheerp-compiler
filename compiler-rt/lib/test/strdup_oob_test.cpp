// RUN: %clangxx_asan -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -O2 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -O3 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -cheerp-linear-output=asmjs -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -cheerp-linear-output=asmjs -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -cheerp-linear-output=asmjs -O2 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -cheerp-linear-output=asmjs -O3 %s -o %t && not %run %t 2>&1 | FileCheck %s

#include <string.h>

char kString[] = "foo";

int main(int argc, char **argv) {
  ++argc;
  char *copy = strdup(kString);
  int x = copy[4 + argc];  // BOOM
  // CHECK: AddressSanitizer: heap-buffer-overflow
  // DONTCHECK: #0 {{.*}}main {{.*}}strdup_oob_test.cpp:[[@LINE-2]]
  // CHECK-LABEL: allocated by thread T{{.*}} here:
  // DONTCHECK: #{{[01]}} {{.*}}strdup
  // DONTCHECK: #{{.*}}main {{.*}}strdup_oob_test.cpp:[[@LINE-6]]
  // CHECK-LABEL: SUMMARY
  // DONTCHECK: strdup_oob_test.cpp:[[@LINE-7]]
  return x;
}
