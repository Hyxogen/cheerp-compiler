#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int __asan_option_detect_stack_use_after_return;

void __asan_init(void) {
        __asan_option_detect_stack_use_after_return = 0;
        *(uint8_t*) 0 = 0xff;
        fprintf(stderr, "initialized asan\n");
}

void __asan_version_mismatch_check_v8(void) {
        //Do nothing

}

void __asan_register_globals(uintptr_t a, uintptr_t b) {
        fprintf(stderr, "registered globals\n");

}

void __asan_unregister_globals(uintptr_t a, uintptr_t b) {
        fprintf(stderr, "unregistered globals\n");

}

void __asan_report_load4(uintptr_t ptr) {
        uint32_t v = ptr;
        fprintf(stderr, "invalid load %x\n", v);
        abort();
}
