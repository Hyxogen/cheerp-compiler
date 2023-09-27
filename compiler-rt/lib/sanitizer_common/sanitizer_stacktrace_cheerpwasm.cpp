#include "sanitizer_common.h"
#include "sanitizer_placement_new.h"
#include "sanitizer_stacktrace.h"
#if SANITIZER_CHEERPWASM

namespace __sanitizer {
void BufferedStackTrace::Unwind(u32 max_depth, uptr pc, uptr bp, void *context,
                                uptr stack_top, uptr stack_bottom,
                                bool request_fast_unwind) {}

void StackTrace::Print() const {}

} // namespace __sanitizer

#endif // SANITIZER_CHEERPWASM
