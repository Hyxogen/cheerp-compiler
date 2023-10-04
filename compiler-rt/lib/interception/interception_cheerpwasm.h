#if SANITIZER_CHEERPWASM

#if !defined(INCLUDED_FROM_INTERCEPTION_LIB)
# error "interception_linux.h should be included from interception library only"
#endif

#ifndef INTERCEPTION_CHEERPWASM_H

#include <cstddef>

extern "C" { 
size_t __cheerp_strlen(const char *s);
size_t __cheerp_strnlen(const char *s, size_t maxlen);
void* __cheerp_memset(void* s, int c, size_t n);
void* __cheerp_memmove(void* d, const void *s, size_t n);
void* __cheerp_memcpy(void* d, const void *s, size_t n);
size_t __cheerp_strlen(const char *s);
char *__cheerp_strcpy(char *d, const char *s);
char *__cheerp_strncpy(char *d, const char *s, size_t n);
char *__cheerp_strcat(char *d, const char *s);
char *__cheerp_strncat(char *d, const char *s, size_t n);
int __cheerp_atoi(const char *s);
long __cheerp_atol(const char *s);
char* __cheerp_strdup(const char * s);
long __cheerp_strtol(const char *s, char **end, int base);
}

namespace __interception {
bool InterceptFunction(const char *name, uptr *ptr_to_real, uptr func);
bool InterceptFunction(const char *name, const char *ver, uptr *ptr_to_real, uptr func);
} // namespace __interception

#define INTERCEPT_FUNCTION_CHEERP(func) \
  ::__interception::InterceptFunction(#func, \
    (::__interception::uptr *) &REAL(func), \
    (::__interception::uptr) &(__cheerp_##func))

#define INTERCEPT_FUNCTION_VER_CHEERP(func, ver) \
  ::__interception::InterceptFunction(#func, ver\
    (::__interception::uptr *) &REAL(func), \
    (::__interception::uptr *) &(__cheerp_##func))

#endif // INTERCEPTION_CHEERPWASM_H

#endif // SANITIZER_CHEERPWASM
