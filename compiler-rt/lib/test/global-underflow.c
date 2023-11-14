// RUN: %clang_asan -O0 %s %p/Helpers/underflow.c -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clang_asan -O1 %s %p/Helpers/underflow.c -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clang_asan -O2 %s %p/Helpers/underflow.c -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clang_asan -O3 %s %p/Helpers/underflow.c -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clang_asan -cheerp-linear-output=asmjs -O0 %s %p/Helpers/underflow.c -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clang_asan -cheerp-linear-output=asmjs -O1 %s %p/Helpers/underflow.c -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clang_asan -cheerp-linear-output=asmjs -O2 %s %p/Helpers/underflow.c -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clang_asan -cheerp-linear-output=asmjs -O3 %s %p/Helpers/underflow.c -o %t && not %run %t 2>&1 | FileCheck %s

int XXX[2] = {2, 3};
extern int YYY[];
#include <string.h>
int main(int argc, char **argv) {
  memset(XXX, 0, 2*sizeof(int));
  // CHECK: {{READ of size 4 at 0x.* thread}}
  // DONTCHECK: {{    #0 0x.* in main .*global-underflow.cpp:}}[[@LINE+3]]
  // DONTCHECK: {{0x.* is located 4 bytes before global variable}}
  // DONTCHECK:   {{.*YYY.* of size 12}}
  int res = YYY[-1];
  return res;
}
