#ifndef SANITIZER_CHEERPWASM_h
#define SANITIZER_CHEERPWASM_h

#include "sanitizer_common.h"
#include <cstring>

__asan::uptr ReadBinaryName(/*out*/char *buf, __asan::uptr buf_len) {
        strncpy(buf, "todo", buf_len);
        return buf_len;
}

__asan::uptr ReadBinaryNameCached(/*out*/char *buf, __asan::uptr buf_len) {
        strncpy(buf, "todo", buf_len);
        return buf_len;
}

#endif
