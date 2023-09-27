#include "sanitizer_platform.h"

#if SANITIZER_CHEERPWASM
#include "sanitizer_symbolizer_internal.h"

namespace __sanitizer {

void Symbolizer::LateInitialize() {}

} // namespace __sanitizer
#endif // SANITIZER_CHEERPWASM
