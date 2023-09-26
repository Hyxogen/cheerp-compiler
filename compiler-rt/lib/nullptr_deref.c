// RUN: %cc_asan -O0 %s -o %t && not node %t 2>&1 | FileCheck %s
// RUN: %cc_asan -O1 %s -o %t && not node %t 2>&1 | FileCheck %s
// RUN: %cc_asan -O2 %s -o %t && not node %t 2>&1 | FileCheck %s
// RUN: %cc_asan -O3 %s -o %t && not node %t 2>&1 | FileCheck %s
int main(void) {
        // CHECK: {{READ of size 4 at 0x.*}}
        return *(volatile int *) 0; // BOOM
}
