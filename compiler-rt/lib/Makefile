TARGET := libasan.bc

CHEERP_DEST := /home/daan/opt/cheerp
CC	:= $(join $(CHEERP_DEST),/bin/clang)
CXX	:= $(join $(CHEERP_DEST),/bin/clang++)
CXXFLAGS := -O0 -g0 -target cheerp-wasm -I. -DSANITIZER_CHEERPWASM=1
LINK_FLAGS := -cheerp-linear-heap-size=2048 -cheerp-wasm-enable=growmem

LINK_CMD := $(join $(CHEERP_DEST),/bin/llvm-link)

OBJ_DIR		:= build
DEP_DIR		:= build

CXX_FILES := \
		asan/asan_allocator.cpp \
  		asan/asan_activation.cpp \
  		asan/asan_debugging.cpp \
  		asan/asan_descriptions.cpp \
  		asan/asan_errors.cpp \
  		asan/asan_fake_stack.cpp \
  		asan/asan_flags.cpp \
  		asan/asan_fuchsia.cpp \
  		asan/asan_globals.cpp \
  		asan/asan_globals_win.cpp \
  		asan/asan_interceptors.cpp \
  		asan/asan_interceptors_memintrinsics.cpp \
  		asan/asan_linux.cpp \
  		asan/asan_mac.cpp \
  		asan/asan_malloc_linux.cpp \
  		asan/asan_malloc_cheerpwasm.cpp \
  		asan/asan_malloc_mac.cpp \
  		asan/asan_malloc_win.cpp \
  		asan/asan_memory_profile.cpp \
  		asan/asan_poisoning.cpp \
  		asan/asan_posix.cpp \
  		asan/asan_premap_shadow.cpp \
  		asan/asan_report.cpp \
  		asan/asan_rtl.cpp \
  		asan/asan_shadow_setup.cpp \
  		asan/asan_stack.cpp \
  		asan/asan_stats.cpp \
  		asan/asan_suppressions.cpp \
  		asan/asan_thread.cpp \
  		asan/asan_win.cpp \
  		asan/asan_cheerpwasm.cpp \
		interception/interception_linux.cpp \
		interception/interception_cheerpwasm.cpp \
  		interception/interception_mac.cpp \
  		interception/interception_win.cpp \
  		interception/interception_type_test.cpp \
		lsan/lsan_common.cpp \
		lsan/lsan_common_cheerpwasm.cpp \
		sanitizer_common/sanitizer_allocator.cpp \
  		sanitizer_common/sanitizer_common.cpp \
  		sanitizer_common/sanitizer_deadlock_detector1.cpp \
  		sanitizer_common/sanitizer_deadlock_detector2.cpp \
  		sanitizer_common/sanitizer_errno.cpp \
  		sanitizer_common/sanitizer_file.cpp \
  		sanitizer_common/sanitizer_flags.cpp \
  		sanitizer_common/sanitizer_flag_parser.cpp \
  		sanitizer_common/sanitizer_fuchsia.cpp \
  		sanitizer_common/sanitizer_libc.cpp \
  		sanitizer_common/sanitizer_libignore.cpp \
  		sanitizer_common/sanitizer_linux.cpp \
  		sanitizer_common/sanitizer_linux_s390.cpp \
  		sanitizer_common/sanitizer_cheerpwasm.cpp \
  		sanitizer_common/sanitizer_cheerpwasm_mmap.cpp \
  		sanitizer_common/sanitizer_mac.cpp \
  		sanitizer_common/sanitizer_mutex.cpp \
  		sanitizer_common/sanitizer_netbsd.cpp \
  		sanitizer_common/sanitizer_platform_limits_freebsd.cpp \
  		sanitizer_common/sanitizer_platform_limits_linux.cpp \
  		sanitizer_common/sanitizer_platform_limits_netbsd.cpp \
  		sanitizer_common/sanitizer_platform_limits_posix.cpp \
  		sanitizer_common/sanitizer_platform_limits_solaris.cpp \
  		sanitizer_common/sanitizer_platform_limits_cheerpwasm.cpp \
  		sanitizer_common/sanitizer_posix.cpp \
  		sanitizer_common/sanitizer_printf.cpp \
  		sanitizer_common/sanitizer_procmaps_common.cpp \
  		sanitizer_common/sanitizer_procmaps_bsd.cpp \
  		sanitizer_common/sanitizer_procmaps_fuchsia.cpp \
  		sanitizer_common/sanitizer_procmaps_linux.cpp \
  		sanitizer_common/sanitizer_procmaps_mac.cpp \
  		sanitizer_common/sanitizer_procmaps_solaris.cpp \
  		sanitizer_common/sanitizer_solaris.cpp \
  		sanitizer_common/sanitizer_stoptheworld_fuchsia.cpp \
  		sanitizer_common/sanitizer_stoptheworld_mac.cpp \
  		sanitizer_common/sanitizer_stoptheworld_win.cpp \
  		sanitizer_common/sanitizer_stoptheworld_cheerpwasm.cpp \
  		sanitizer_common/sanitizer_suppressions.cpp \
  		sanitizer_common/sanitizer_tls_get_addr.cpp \
  		sanitizer_common/sanitizer_thread_registry.cpp \
  		sanitizer_common/sanitizer_type_traits.cpp \
  		sanitizer_common/sanitizer_termination.cpp \
  		sanitizer_common/sanitizer_stacktrace_cheerpwasm.cpp \
  		sanitizer_common/sanitizer_win.cpp \
		sanitizer_common/sanitizer_allocator_report.cpp \
  		sanitizer_common/sanitizer_chained_origin_depot.cpp \
  		sanitizer_common/sanitizer_stack_store.cpp \
  		sanitizer_common/sanitizer_stackdepot.cpp \
  		sanitizer_common/sanitizer_stacktrace.cpp \
  		sanitizer_common/sanitizer_stacktrace_libcdep.cpp \
  		sanitizer_common/sanitizer_stacktrace_printer.cpp \
  		sanitizer_common/sanitizer_stacktrace_sparc.cpp \
  		sanitizer_common/sanitizer_symbolizer.cpp \
  		sanitizer_common/sanitizer_symbolizer_libbacktrace.cpp \
  		sanitizer_common/sanitizer_symbolizer_libcdep.cpp \
  		sanitizer_common/sanitizer_symbolizer_mac.cpp \
  		sanitizer_common/sanitizer_symbolizer_markup.cpp \
  		sanitizer_common/sanitizer_symbolizer_posix_libcdep.cpp \
  		sanitizer_common/sanitizer_symbolizer_report.cpp \
  		sanitizer_common/sanitizer_symbolizer_win.cpp \
  		sanitizer_common/sanitizer_symbolizer_cheerpwasm.cpp \
  		sanitizer_common/sanitizer_unwind_linux_libcdep.cpp \
  		sanitizer_common/sanitizer_unwind_win.cpp

HEADER_DEPS	:= $(addprefix $(DEP_DIR)/,$(CXX_FILES:.cpp=.d))
OBJ_FILES	:= $(addprefix $(OBJ_DIR)/,$(CXX_FILES:.cpp=.bc))

$(TARGET): $(OBJ_FILES)
	$(LINK_CMD) -o $@ $(OBJ_FILES)

-include $(HEADER_DEPS)
$(OBJ_DIR)/%.bc: %.cpp Makefile
	mkdir -p $(@D)
	$(CXX) -o $@ $< $(CXXFLAGS) -c -MMD

.PHONY: test
test: $(TARGET)
	#$(CC) $(LINK_FLAGS) strcasestr_strict.c libasan.bc -fsanitize=address -g0 -cheerp-pretty-code -target cheerp-wasm -Itest
	$(CXX) $(LINK_FLAGS) leaks.cpp libasan.bc -fsanitize=address -g0 -cheerp-pretty-code -target cheerp-wasm -Itest

.PHONY: run
run: test
	node a.out


.PHONY: clean
clean:
	rm -f $(OBJ_FILES) $(HEADER_DEPS) $(TEST_FILES)
	rm -f $(TARGET)
