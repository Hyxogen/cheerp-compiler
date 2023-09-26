#ifndef SANITIZER_CHEERPWASM_MMAP_H
#define SANITIZER_CHEERPWASM_MMAP_H

#if SANITIZER_CHEERPWASM
#include "sanitizer_internal_defs.h"

namespace __sanitizer {

uptr InternalMmap(uptr addr, uptr len, int prot, int flags, int fildes);
void InternalMunmap(uptr addr, uptr len);
void SetupMemoryMapping();

}
#endif // SANITIZER_CHEERPWASM
#endif // SANITIZER_CHEERPWASM_MMAP_H
