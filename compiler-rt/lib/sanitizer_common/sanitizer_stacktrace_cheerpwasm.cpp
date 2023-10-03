#include "sanitizer_common.h"
#include "sanitizer_placement_new.h"
#include "sanitizer_stacktrace.h"
#if SANITIZER_CHEERPWASM

#include <cuchar>
#include <cstdio>

#define LEAN_CXX_LIB
#include <client/cheerp/types.h>

namespace __sanitizer {

static uptr _prev_trace_len = 0;
static uptr _prev_trace[256];

[[cheerp::genericjs]] uptr ConvertFrameToPC(client::String* frame) {
  if (client::TArray<client::String>* match = frame->match("\\bwasm-function\\[\\d+\\]:(0x[0-9a-f]+)")) {
    uptr pc = 0;
    __asm__("%1[1]" : "=r"(pc) : "r"(match));
    return pc;
  } else if (client::TArray<client::String>* match = frame->match(":(\\d+):\\d+(?:\\)|$)")) {
    uptr pc = 0;
    __asm__("%1[1]" : "=r"(pc) : "r"(match));
    return 0x80000000 | pc;
  }
  return 0;
}

[[cheerp::genericjs]] uptr GetCallstack(uptr* dest, uptr dest_len) {
  //client::String* trace = nullptr;
  client::TArray<client::String>* callstack = nullptr;
  __asm__("(new Error()).stack.toString().split('\\n')" : "=r"(callstack) : );

  uptr j = 0;
  for (uptr i = 0; j < dest_len && i < callstack->get_length(); ++i) {
    client::String* frame = (*callstack)[i];

    if (frame->startsWith("Error"))
      continue;

    uptr pc = ConvertFrameToPC(frame);
    dest[j++] = pc;

    if (pc == 0) {
      break;
    }
  }
  return j;
}

void BufferedStackTrace::UnwindFast(uptr pc, uptr bp, uptr stack_top, uptr stack_bottom,
                u32 max_depth) {
  size = _prev_trace_len > kStackTraceMax ? kStackTraceMax : _prev_trace_len;
  internal_memcpy(trace_buffer, _prev_trace, size * sizeof(_prev_trace[0]));
  trace_buffer[0] = pc;
}

uptr StackTrace::GetCurrentPc() {
  _prev_trace_len = GetCallstack(_prev_trace, sizeof(_prev_trace)/sizeof(_prev_trace[0]));
  if (_prev_trace_len) {
    return _prev_trace[0];
  }
  return 0;
}

} // namespace __sanitizer

#endif // SANITIZER_CHEERPWASM
