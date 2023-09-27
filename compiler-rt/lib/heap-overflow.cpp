// RUN: %cc_asan -O0 %s -o %t && not node %t 2>&1 | FileCheck %s
// RUN: %cc_asan -O1 %s -o %t && not node %t 2>&1 | FileCheck %s
// RUN: %cc_asan -O2 %s -o %t && not node %t 2>&1 | FileCheck %s
// RUN: %cc_asan -O3 %s -o %t && not node %t 2>&1 | FileCheck %s

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

int main(int argc, char **argv) {
  char *x = (char*)malloc(10 * sizeof(char));
  printf("argc: %i\n", argc);
  printf("allocated ptr: %p\n", (void*) x);
  //printf("will access: %p\n", (void*) &x[(argc + 1) * 10]);
  //memset(x, 0, 10);
  int res = x[(argc + 1) * 10];  // BOOOM
  // CHECK: {{READ of size 1 at 0x.*}}
  free(x);
  return res;
}

