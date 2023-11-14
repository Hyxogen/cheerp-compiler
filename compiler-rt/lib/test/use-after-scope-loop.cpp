// RUN: %clangxx_asan -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -cheerp-linear-output=asmjs -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s

int *p[3];

int main() {
  for (int i = 0; i < 3; i++) {
    int x;
    p[i] = &x;
  }
  return **p;  // BOOM
  // CHECK: ERROR: AddressSanitizer: stack-use-after-scope
  // DONTCHECK: #0 0x{{.*}} in main {{.*}}.cpp:[[@LINE-2]]
}
