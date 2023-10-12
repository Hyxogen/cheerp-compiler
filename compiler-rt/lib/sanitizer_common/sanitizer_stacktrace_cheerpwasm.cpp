#include "sanitizer_common.h"
#include "sanitizer_placement_new.h"
#include "sanitizer_stacktrace.h"
#if SANITIZER_CHEERPWASM

#include <cstdio>
#include <cuchar>

#define LEAN_CXX_LIB
#include <client/cheerp/types.h>

namespace __sanitizer {

static uptr _prev_trace_len = 0;
static uptr _prev_trace[256];
static [[cheerp::genericjs]] client::Object* _symbols = nullptr;
static char _name_cache[256];
static uptr _name_len = 0;

[[cheerp::genericjs]] static uptr ConvertFrameToPC(client::String* frame) {
  if (client::TArray<client::String>* match = frame->match("\\bwasm-function\\[\\d+\\]:(0x[0-9a-f]+)")) {
    if (match->get_length() >= 2) {
      uptr pc = 0;
      __asm__("%1[1]" : "=r"(pc) : "r"(match));
      return pc;
    }
  }
  if (client::TArray<client::String>* match = frame->match(":(\\d+):\\d+(?:\\)|$)")) {
    if (match->get_length() >= 2) {
      uptr pc = 0;
      __asm__("%1[1]" : "=r"(pc) : "r"(match));
      return 0x80000000 | pc;
    }
  }
  return 0;
}

[[cheerp::genericjs]] static void CachePC(uptr pc, client::String* frame) {
  if (_symbols == nullptr) {
    __asm__("{}" : "=r"(_symbols));
  }
  __asm__("%0[%1]=%2" : : "r"(_symbols), "r"(pc), "r"(frame));
}

[[cheerp::genericjs]] static uptr GetCallstack(uptr* dest, uptr dest_len) {
  client::TArray<client::String>* callstack = nullptr;
  __asm__("(new Error()).stack.toString().split('\\n')" : "=r"(callstack) : );

  uptr j = 0;
  for (uptr i = 0; j < dest_len && i < callstack->get_length(); ++i) {
    client::String* frame = (*callstack)[i];

    if (frame->startsWith("Error"))
      continue;

    uptr pc = ConvertFrameToPC(frame);
    CachePC(pc, frame);
    dest[j++] = pc;

    if (pc == 0) {
      break;
    }
  }
  return j;
}

[[cheerp::genericjs]] static client::String* GetFunctionAtPC(uptr pc) {
  if (_symbols == nullptr)
    return nullptr;

  client::String* result = nullptr;
  __asm__("%1[%2]" : "=r"(result) : "r"(_symbols), "r"(pc));
  bool res = false;
  __asm__("!!%1" : "=r"(res) : "r"(result));
  if (res)
    return result;
  return 0;
} 

[[cheerp::genericjs]] static uptr ReadJSString(client::String* str, char16_t* dest, uptr len) {
  uptr i = 0;
  for (; i < len && i < str->get_length(); ++i) {
    dest[i] = str->charCodeAt(i);
  }
  return i;
}

[[cheerp::genericjs]] static uptr GetFunctionNameAtPC16(uptr pc, char16_t* dest, uptr len) {
  client::String* frame = GetFunctionAtPC(pc);

  if (frame) {
    if (client::TArray<client::String>* match = frame->match("^\\s+at (.*) \\(.*\\)$")) {
      return ReadJSString((*match)[1], dest, len);
    } else if (client::TArray<client::String>* match = frame->match("^(.+?)@")) {
      return ReadJSString((*match)[1], dest, len);
    }
  }
  return 0;
}

static uptr ConvertJSString(char *dest, uptr dlen, const char16_t* src, uptr slen) {
  uptr res_len = slen < dlen ? slen : dlen;

  mbstate_t state{};
  for (uptr i = 0; i < res_len; ++i) {
    size_t rc = c16rtomb(dest, src[i], &state);
    if (rc == (size_t) -1) {
      return -1;
    }
    dest += rc;
  }
  return res_len;
}

const char* GetFunctionNameAtPC(uptr pc) {
  char16_t buffer[256];
  uptr buffer_len = GetFunctionNameAtPC16(pc, buffer, sizeof(buffer) / sizeof(buffer[0]));
  _name_len =
      ConvertJSString(_name_cache, (sizeof(_name_cache) / sizeof(_name_cache[0])) - 1,
                      buffer, buffer_len);
  if (_name_len == -1) {
    _name_len = 0;
    return nullptr;
  }
  _name_cache[_name_len] = 0;
  return _name_cache;
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
