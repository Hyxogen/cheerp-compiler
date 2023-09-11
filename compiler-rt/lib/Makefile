TARGET := libasan.bc

CXX	:= /home/daan/opt/cheerp/bin/clang++
CXXFLAGS := -O0 -g0 -target cheerp-wasm -I. -DSANITIZER_CHEERPWASM

LINK_CMD := /home/daan/opt/cheerp/bin/llvm-link

CXX_FILES := \
	     asan/asan_activation.cpp \
	     asan/asan_allocator.cpp \
	     asan/asan_cheerpwasm.cpp \
	     asan/asan_debugging.cpp \
	     asan/asan_descriptions.cpp \
	     asan/asan_errors.cpp \
	     asan/asan_fake_stack.cpp \
	     asan/asan_flags.cpp \
	     asan/asan_globals.cpp \
	     asan/asan_interceptors.cpp \
	     asan/asan_interceptors_memintrinsics.cpp \
	     asan/asan_memory_profile.cpp \
	     asan/asan_new_delete.cpp \
	     asan/asan_poisoning.cpp \
	     asan/asan_preinit.cpp \
	     asan/asan_premap_shadow.cpp \
	     asan/asan_report.cpp \
	     asan/asan_rtl.cpp \
	     asan/asan_rtl_static.cpp \
	     asan/asan_shadow_setup.cpp \
	     asan/asan_stack.cpp \
	     asan/asan_stats.cpp \
	     asan/asan_suppressions.cpp \
	     asan/asan_thread.cpp \
	     sanitizer_common/sancov_flags.cpp \
	     sanitizer_common/sanitizer_allocator_checks.cpp \
	     sanitizer_common/sanitizer_allocator.cpp \
	     sanitizer_common/sanitizer_allocator_report.cpp \
	     sanitizer_common/sanitizer_chained_origin_depot.cpp \
	     sanitizer_common/sanitizer_common.cpp \
	     sanitizer_common/sanitizer_common_nolibc.cpp \
	     sanitizer_common/sanitizer_coverage_libcdep_new.cpp \
	     sanitizer_common/sanitizer_deadlock_detector1.cpp \
	     sanitizer_common/sanitizer_deadlock_detector2.cpp \
	     sanitizer_common/sanitizer_errno.cpp \
	     sanitizer_common/sanitizer_file.cpp \
	     sanitizer_common/sanitizer_flag_parser.cpp \
	     sanitizer_common/sanitizer_flags.cpp \
	     sanitizer_common/sanitizer_libc.cpp \
	     sanitizer_common/sanitizer_libignore.cpp \
	     sanitizer_common/sanitizer_mutex.cpp \
	     sanitizer_common/sanitizer_printf.cpp \
	     sanitizer_common/sanitizer_procmaps_common.cpp \
	     sanitizer_common/sanitizer_solaris.cpp \
	     sanitizer_common/sanitizer_stackdepot.cpp \
	     sanitizer_common/sanitizer_stack_store.cpp \
	     sanitizer_common/sanitizer_stacktrace.cpp \
	     sanitizer_common/sanitizer_stacktrace_libcdep.cpp \
	     sanitizer_common/sanitizer_stacktrace_printer.cpp \
	     sanitizer_common/sanitizer_suppressions.cpp \
	     sanitizer_common/sanitizer_symbolizer.cpp \
	     sanitizer_common/sanitizer_symbolizer_libbacktrace.cpp \
	     sanitizer_common/sanitizer_symbolizer_libcdep.cpp \
	     sanitizer_common/sanitizer_symbolizer_markup.cpp \
	     sanitizer_common/sanitizer_symbolizer_report.cpp \
	     sanitizer_common/sanitizer_termination.cpp \
	     sanitizer_common/sanitizer_thread_registry.cpp \
	     sanitizer_common/sanitizer_tls_get_addr.cpp \
	     sanitizer_common/sanitizer_type_traits.cpp # \
	     sanitizer_common/sanitizer_common_libcdep.cpp 
HEADER_DEPS	:= $(CXX_FILES:.cpp=.d)
OBJ_FILES	:= $(CXX_FILES:.cpp=.bc)

$(TARGET): $(OBJ_FILES)
	$(LINK_CMD) -o $@ $(OBJ_FILES)

-include $(HEADER_DEPS)
%.bc: %.cpp Makefile
	$(CXX) -o $@ $< $(CXXFLAGS) -c -MMD

clean:
	rm -f $(OBJ_FILES) $(HEADER_DEPS)

	#     asan/asan_linux.cpp \
	     asan/asan_malloc_linux.cpp \
