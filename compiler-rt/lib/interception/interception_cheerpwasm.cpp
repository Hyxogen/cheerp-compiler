#include "interception.h"

#if SANITIZER_CHEERPWASM
#include <cstdio>
namespace __interception {


bool InterceptFunction(const char *name, uptr *ptr_to_real, uptr func) {
  printf("%s: *%p = %p\n", name, (void*) ptr_to_real, (void*) func);
  *ptr_to_real = func;
  return true;
}

}  // namespace __interception

#endif // SANITIZER_CHEERPWASM
