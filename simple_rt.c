#include <stdio.h>
#include <stdint.h>

int __asan_option_detect_stack_use_after_return;

void __asan_init(void) {
        __asan_option_detect_stack_use_after_return = 0;
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
        (void) ptr;
        fprintf(stderr, "load of ptr\n");
        if (ptr == 0) {
                fprintf(stderr, "load of nullptr\n");
        } else {
                fprintf(stderr, "load of other ptr\n");
        }
}
