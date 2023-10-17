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

/// Checks if an address is poisoned.
///
/// Returns 1 if <c><i>addr</i></c> is poisoned (that is, 1-byte read/write
/// access to this address would result in an error report from ASan).
/// Otherwise returns 0.
///
/// \param addr Address to check.
///
/// \retval 1 Address is poisoned.
/// \retval 0 Address is not poisoned.
int __asan_address_is_poisoned(void const volatile *addr);

/// Checks if a region is poisoned.
///
/// If at least one byte in <c>[beg, beg+size)</c> is poisoned, returns the
/// address of the first such byte. Otherwise returns 0.
///
/// \param beg Start of memory region.
/// \param size Start of memory region.
/// \returns Address of first poisoned byte.
void *__asan_region_is_poisoned(void *beg, size_t size);

/// Gets information about a pointer (useful for calling from the debugger).
///
/// Returns the category of the given pointer as a constant string.
/// Possible return values are <c>global</c>, <c>stack</c>, <c>stack-fake</c>,
/// <c>heap</c>, <c>heap-invalid</c>, <c>shadow-low</c>, <c>shadow-gap</c>,
/// <c>shadow-high</c>, and <c>unknown</c>.
///
/// If the return value is <c>global</c> or <c>stack</c>, tries to also return
/// the variable name, address, and size. If the return value is <c>heap</c>,
/// tries to return the chunk address and size. <c><i>name</i></c> should point
/// to an allocated buffer of size <c><i>name_size</i></c>.
///
/// \param addr Address to locate.
/// \param name Buffer to store the variable's name.
/// \param name_size Size in bytes of the variable's name buffer.
/// \param[out] region_address Address of the region.
/// \param[out] region_size Size of the region in bytes.
///
/// \returns Returns the category of the given pointer as a constant string.
const char *__asan_locate_address(void *addr, char *name, size_t name_size,
                                  void **region_address, size_t *region_size);

/// Gets the current shadow memory mapping (useful for calling from the
/// debugger).
///
/// \param[out] shadow_scale Shadow scale value.
/// \param[out] shadow_offset Offset value.
void __asan_get_shadow_mapping(size_t *shadow_scale, size_t *shadow_offset);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SANITIZER_ASAN_INTERFACE_H
