#include "sanitizer_common.h"
#include "sanitizer_placement_new.h"
#include "sanitizer_stacktrace.h"
#if SANITIZER_CHEERPWASM

#include <client/cheerp/jsobject.h>
#include <cuchar>
#include <cstdio>

namespace [[cheerp::genericjs]] client {
  class String: public Object {
  public:
    int get_length() const;
    int charCodeAt(int i) const;
  };
}

namespace __sanitizer {


[[cheerp::genericjs]] uptr GetTrace(char16_t* buffer, uptr len) {
  client::String* trace = nullptr;
  __asm__("(new Error()).stack" : "=r"(trace) : );

  uptr trace_len = static_cast<uptr>(trace->get_length());
  uptr res_len = trace_len > len ? len : trace_len;

  for (uptr i = 0; i < res_len; ++i) {
    buffer[i] = static_cast<char16_t>(trace->charCodeAt(static_cast<int>(i)));
  }

  return res_len;
}

uptr ConvertJSString(char *dest, uptr dlen, const char16_t* src, uptr slen) {
  uptr res_len = slen < dlen ? slen : dlen;

  mbstate_t state{};
  for (uptr i = 0; i < res_len; ++i) {
    size_t rc = c16rtomb(dest, src[i], &state);
    if (rc == (size_t) -1)
      break;
    dest += rc;
  }
  return res_len;
}

void BufferedStackTrace::UnwindHere() {
  char16_t buffer[4096];
  uptr buffer_len = GetTrace(buffer, sizeof(buffer)/sizeof(buffer[0]));
  size = ConvertJSString(_trace, sizeof(_trace), buffer, buffer_len);
  trace = reinterpret_cast<uptr*>(&_trace[0]);
}

void BufferedStackTrace::Unwind(uptr pc, uptr bp, void *context, bool request_fast,
            u32 max_depth) {
  UnwindHere();
}

void BufferedStackTrace::Unwind(u32 max_depth, uptr pc, uptr bp, void *context,
                                uptr stack_top, uptr stack_bottom,
                                bool request_fast_unwind) {
  UnwindHere();
}

void StackTrace::Print() const {
  fwrite(reinterpret_cast<const char*>(trace), 1, size, stderr);
}

uptr StackTrace::GetCurrentPc() { return 0; }
//u32 StackDepotPut(StackTrace stack) { return 0; } // CHEERPASAN: TODO this should not be stubbed like this, most likely we need the actual implementation in sanitizer_stackdepot.cpp

} // namespace __sanitizer

#endif // SANITIZER_CHEERPWASM
