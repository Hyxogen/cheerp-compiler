#include "sanitizer_platform.h"

#if SANITIZER_CHEERPWASM
#include "sanitizer_symbolizer_internal.h"

namespace __sanitizer {

void Symbolizer::LateInitialize() {}
void ScopedErrorReportLock::Lock() {}
bool ColorizeReports() { return false; }
void ReportErrorSummary(const char *error_type, const StackTrace *stack,
                        const char *alt_tool_name) {}

} // namespace __sanitizer
#endif // SANITIZER_CHEERPWASM
