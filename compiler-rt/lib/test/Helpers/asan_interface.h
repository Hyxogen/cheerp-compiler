#ifndef SANITIZER_ASAN_INTERFACE_H
#define SANITIZER_ASAN_INTERFACE_H

#include "common_interface_defs.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Marks a memory region (<c>[addr, addr+size)</c>) as unaddressable.
///
/// This memory must be previously allocated by your program. Instrumented
/// code is forbidden from accessing addresses in this region until it is
/// unpoisoned. This function is not guaranteed to poison the entire region -
/// it could poison only a subregion of <c>[addr, addr+size)</c> due to ASan
/// alignment restrictions.
///
/// \note This function is not thread-safe because no two threads can poison or
/// unpoison memory in the same memory region simultaneously.
///
/// \param addr Start of memory region.
/// \param size Size of memory region.
void __asan_poison_memory_region(void const volatile *addr, size_t size);

/// Describes an address (useful for calling from the debugger).
///
/// Prints the description of <c><i>addr</i></c>.
///
/// \param addr Address to describe.
void __asan_describe_address(size_t addr);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SANITIZER_ASAN_INTERFACE_H
