#ifndef SANITIZER_CHEERPWASM_H
#define SANITIZER_CHEERPWASM_H

#include "sanitizer_platform.h"

#if SANITIZER_CHEERPWASM

#include "sanitizer_internal_defs.h"

namespace __sanitizer {

uptr internal_write(fd_t fd, const void *buf, uptr count);

} // namespace __sanitizer

#endif // SANITIZER_CHEERPWASM

#endif // SANITIZER_CHEERPWASM_H
