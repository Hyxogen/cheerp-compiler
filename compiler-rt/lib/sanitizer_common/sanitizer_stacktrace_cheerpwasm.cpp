#include "sanitizer_common.h"
#include "sanitizer_placement_new.h"
#include "sanitizer_stacktrace.h"
#if SANITIZER_CHEERPWASM

#  include <cstdio>
#  include <cuchar>

// We have to define LEAN_CXX_LIB as client lib defines it own new operator
// which conflicts with the one that asan declares
#  define LEAN_CXX_LIB
#  include <client/cheerp/types.h>

// The sanitizer are able to output stacktraces to give more context of where
// something happened. One might expect that this would be implemented by
// calling the stack unwinder and explicitly tell it how many functions to skip.
// However, the sanitizer_common library doesn't work like that. It uses
// GET_CALLER_PC_BP_SP and GET_CURRENT_PC_BP_SP. Then is passes the PC, BP and
// SP values along until some other function uses those values to actually
// unwind the stack. On standard machines, the stack can be unwound by treating
// BP as a linked list. But on cheerp, BP does not exist. Therefore we must be
// able to unwind from a PC value that may no longer be on the execution stack,
// and thus are forced to cache the entire call stack.

namespace __sanitizer {

static uptr _prev_trace_len = 0;
static uptr _prev_trace[256];
static [[cheerp::genericjs]] client::Object* _symbols = nullptr;
static char _name_cache[256];
static uptr _name_len = 0;

[[cheerp::genericjs]] static uptr ConvertFrameToPc(client::String* frame) {
  if (client::TArray<client::String>* match =
          frame->match("\\bwasm-function\\[\\d+\\]:(0x[0-9a-f]+)")) {
    if (match->get_length() >= 2) {
      uptr pc = 0;
      __asm__("%1[1]" : "=r"(pc) : "r"(match));
      return pc;
    }
  }
  if (client::TArray<client::String>* match =
          frame->match(":(\\d+):\\d+(?:\\)|$)")) {
    if (match->get_length() >= 2) {
      uptr pc = 0;
      __asm__("%1[1]" : "=r"(pc) : "r"(match));
      return 0x80000000 | pc;
    }
  }
  return 0;
}

[[cheerp::genericjs]] static void CachePc(uptr pc, client::String* frame) {
  if (UNLIKELY(_symbols == nullptr)) {
    __asm__("{}" : "=r"(_symbols));
  }
  __asm__("%0[%1]=%2" : : "r"(_symbols), "r"(pc), "r"(frame));
}

[[cheerp::genericjs]] static uptr GetCallstack(uptr* dest, uptr dest_len) {
  client::TArray<client::String>* callstack = nullptr;
  __asm__("(new Error()).stack.toString().split('\\n')" : "=r"(callstack));

  uptr j = 0;
  for (uptr i = 0; j < dest_len && i < callstack->get_length(); ++i) {
    client::String* frame = (*callstack)[i];

    if (frame->startsWith("Error"))
      continue;

    uptr pc = ConvertFrameToPc(frame);
    CachePc(pc, frame);
    dest[j++] = pc;

    if (pc == 0) {
      break;
    }
  }
  return j;
}

[[cheerp::genericjs]] static client::String* GetFunctionAtPc(uptr pc) {
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

[[cheerp::genericjs]] static uptr ReadJSString(client::String* str,
                                               char16_t* dest, uptr len) {
  uptr i = 0;
  for (; i < len && i < str->get_length(); ++i) {
    dest[i] = str->charCodeAt(i);
  }
  return i;
}

[[cheerp::genericjs]] static uptr GetUtf16FunctionNameAtPc(uptr pc,
                                                           char16_t* dest,
                                                           uptr len) {
  client::String* frame = GetFunctionAtPc(pc);

  if (frame) {
    if (client::TArray<client::String>* match =
            frame->match("^\\s+at (.*) \\(.*\\)$")) {
      return ReadJSString((*match)[1], dest, len);
    } else if (client::TArray<client::String>* match =
                   frame->match("^(.+?)@")) {
      return ReadJSString((*match)[1], dest, len);
    }
  }
  return 0;
}

#  define REPLACEMENT_CHARACTER 0xFFFD
#  define MAX_CODEPOINT 0x10FFFF
#  define INVALID_CODEPOINT -1

static uptr CodepointToUtf8(char* dest, char32_t codepoint) {
  char buffer[4];

  if (!dest)
    dest = buffer;

  if (codepoint > MAX_CODEPOINT) {
    codepoint = REPLACEMENT_CHARACTER;
  }

  if (codepoint <= 0x7F) {
    *dest = static_cast<char>(codepoint);

    return 1;
  } else if (codepoint <= 0x7FF) {
    dest[0] = 0xC0 | (codepoint >> 6);
    dest[1] = 0x80 | (codepoint & 63);

    return 2;
  } else if (codepoint <= 0xFFFF) {
    dest[0] = 0xE0 | (codepoint >> 12);
    dest[1] = 0x80 | ((codepoint >> 6) & 63);
    dest[2] = 0x80 | (codepoint & 63);

    return 3;
  }

  dest[0] = 0xF0 | (codepoint >> 18);
  dest[1] = 0x80 | ((codepoint >> 12) & 63);
  dest[2] = 0x80 | ((codepoint >> 6) & 63);
  dest[3] = 0x80 | (codepoint & 63);
  return 4;
}

static uptr Utf16ToUtf8(char* dest, uptr dlen, const char16_t* src, uptr slen) {
  if (dlen == 0)
    return 0;

  uptr j = 0;
  for (uptr i = 0; i < slen; ++i) {
    uint32_t codepoint = src[i];

    if (codepoint >= 0xD800 && codepoint <= 0xDFFF) {
      if (i + 1 < slen) {
        uint32_t trail = src[++i];
        codepoint = 0x10000 + ((codepoint & 0x3FF) | (trail & 0x3FF));
      } else {
        // Missing lower surrogate
        codepoint = INVALID_CODEPOINT;
      }
    }

    const uptr n = CodepointToUtf8(nullptr, codepoint);
    if (i + n >= dlen)
      break;

    CodepointToUtf8(&dest[j], codepoint);
    j += n;
  }

  dest[j] = 0;
  return j ? j - 1 : 0;
}

const char* GetFunctionNameAtPc(uptr pc) {
  char16_t buffer[256];
  uptr buffer_len =
      GetUtf16FunctionNameAtPc(pc, buffer, sizeof(buffer) / sizeof(buffer[0]));
  _name_len = Utf16ToUtf8(_name_cache,
                          (sizeof(_name_cache) / sizeof(_name_cache[0])) - 1,
                          buffer, buffer_len);
  return _name_cache;
}

void BufferedStackTrace::UnwindFast(uptr pc, uptr bp, uptr stack_top,
                                    uptr stack_bottom, u32 max_depth) {
  size = _prev_trace_len > kStackTraceMax ? kStackTraceMax : _prev_trace_len;
  internal_memcpy(trace_buffer, _prev_trace, size * sizeof(_prev_trace[0]));
  trace_buffer[0] = pc;
}

uptr StackTrace::GetCurrentPc() {
  _prev_trace_len =
      GetCallstack(_prev_trace, sizeof(_prev_trace) / sizeof(_prev_trace[0]));
  if (_prev_trace_len) {
    return _prev_trace[0];
  }
  return 0;
}

}  // namespace __sanitizer

#endif  // SANITIZER_CHEERPWASM
