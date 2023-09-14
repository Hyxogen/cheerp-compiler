//===-- asan_mapping_emscripten.h -------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// Emscripten-specific definitions for ASan memory mapping.
//===----------------------------------------------------------------------===//
#ifndef ASAN_MAPPING_CHEERPWASM_H
#define ASAN_MAPPING_CHEERPWASM_H

// || `[0x38000000, 0xffffffff]` || HighMem    ||
// || `[0x27000000, 0x37ffffff]` || HighShadow ||
// || `[0x24000000, 0x26ffffff]` || ShadowGap  ||
// || `[0x20000000, 0x23ffffff]` || LowShadow  ||
// || `[0x00000000, 0x1fffffff]` || LowMem     ||

#define WASM_PAGE_SIZE 65536

#define kLowMemBeg     ((uptr) 0x00000000)

#define kLowMemEnd     ((uptr) 0x1fffffff)

#define kHighMemBeg    ((uptr) 0x38000000)
#define kHighMemEnd    ((uptr) 0xffffffff)

#define kLowShadowBeg  ((uptr) 0x20000000)
#define kLowShadowEnd  ((uptr) 0x23ffffff)

#define kHighShadowBeg ((uptr) 0x27000000)
#define kHighShadowEnd ((uptr) 0x37000000)

#define kMidShadowBeg  0
#define kMidShadowEnd  0

#define kShadowGapBeg  ((uptr) (kLowShadowEnd + 1))
#define kShadowGapEnd  ((uptr) (kHighShadowBeg - 1))

#define kShadowGap2Beg 0
#define kShadowGap2End 0

#define kShadowGap3Beg 0
#define kShadowGap3End 0

// The first 1/8 of the shadow memory space is shadowing itself.
// This allows attempted accesses into the shadow memory, as well as null
// pointer dereferences, to be detected properly.
// The shadow memory of the shadow memory is poisoned.
#define MEM_TO_SHADOW(mem) ((mem) >> ASAN_SHADOW_SCALE)
#define SHADOW_TO_MEM(mem) ((mem) << ASAN_SHADOW_SCALE)

// CHEERP: TODO uncomment PROFILE_ASAN_MAPPING
namespace __asan {

static inline bool AddrIsInLowMem(uptr a) {
  //PROFILE_ASAN_MAPPING();
  return a >= kLowMemBeg && a <= kLowMemEnd;
}

static inline bool AddrIsInLowShadow(uptr a) {
  //PROFILE_ASAN_MAPPING();
  return a >= kLowShadowBeg && a <= kLowShadowEnd;
}

static inline bool AddrIsInMidMem(uptr a) {
  //PROFILE_ASAN_MAPPING();
  return false;
}

static inline bool AddrIsInMidShadow(uptr a) {
  //PROFILE_ASAN_MAPPING();
  return false;
}

static inline bool AddrIsInHighMem(uptr a) {
  //PROFILE_ASAN_MAPPING();
  return false;
  return a >= kHighMemBeg && a <= kHighMemEnd;
}

static inline bool AddrIsInHighShadow(uptr a) {
  //PROFILE_ASAN_MAPPING();
  return a >= kHighShadowBeg && a <= kHighShadowEnd;
}

static inline bool AddrIsInShadowGap(uptr a) {
  //PROFILE_ASAN_MAPPING();
  return a >= kShadowGapBeg && a <= kShadowGapEnd;
}

}  // namespace __asan

#endif  // ASAN_MAPPING_CHEERPWASM_H
