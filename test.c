#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//extern char *__asan_shadow;
extern char __asan_shadow[];
extern uintptr_t _heapStart;
extern uintptr_t _heapEnd;

int main(void) {
  fprintf(stdout, "__asan_shadow %p, _heapStart: %p, _heapEnd: %p\n",
          (void *)&__asan_shadow, (void *)_heapStart, (void *)_heapEnd);
}
