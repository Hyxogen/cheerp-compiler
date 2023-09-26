TARGET := libasan.bc

CC	:= /home/daan/opt/cheerp/bin/clang
CXX	:= /home/daan/opt/cheerp/bin/clang++
CXXFLAGS := -O0 -g0 -target cheerp-wasm -I. -DSANITIZER_CHEERPWASM=1

LINK_CMD := /home/daan/opt/cheerp/bin/llvm-link

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
  		interception/interception_mac.cpp \
  		interception/interception_win.cpp \
  		interception/interception_type_test.cpp \
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
  		sanitizer_common/sanitizer_mac.cpp \
  		sanitizer_common/sanitizer_mutex.cpp \
  		sanitizer_common/sanitizer_netbsd.cpp \
  		sanitizer_common/sanitizer_platform_limits_freebsd.cpp \
  		sanitizer_common/sanitizer_platform_limits_linux.cpp \
  		sanitizer_common/sanitizer_platform_limits_netbsd.cpp \
  		sanitizer_common/sanitizer_platform_limits_posix.cpp \
  		sanitizer_common/sanitizer_platform_limits_solaris.cpp \
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
  		sanitizer_common/sanitizer_suppressions.cpp \
  		sanitizer_common/sanitizer_tls_get_addr.cpp \
  		sanitizer_common/sanitizer_thread_registry.cpp \
  		sanitizer_common/sanitizer_type_traits.cpp \
  		sanitizer_common/sanitizer_win.cpp

HEADER_DEPS	:= $(CXX_FILES:.cpp=.d)
OBJ_FILES	:= $(CXX_FILES:.cpp=.bc)

TEST_CFLAGS	:= -fsanitize=address
TEST_C_FILES	:= \
		   tests/nullptr_deref.c \
		   tests/global-overflow.c

$(TARGET): $(OBJ_FILES)
	$(LINK_CMD) -o $@ $(OBJ_FILES)

-include $(HEADER_DEPS)
%.bc: %.cpp Makefile
	$(CXX) -o $@ $< $(CXXFLAGS) -c -MMD

.PHONY: test
test: $(TARGET)
	-@rc=0; count=0; res=0; \
	for file in $(TEST_C_FILES); do \
		./test.sh "$$file"; \
		res="$$?"; \
		if [ "$$res" -eq 0 ]; \
		then printf PASSED; \
		else printf FAILED; \
		fi; \
		echo "	$$file"; \
		rc=`expr $$rc + $$(($$res != 0))`; count=`expr $$count + 1`; \
	done; \
	echo; echo "Executed $$count tests	Failed tests $$rc"


.PHONY: clean
clean:
	rm -f $(OBJ_FILES) $(HEADER_DEPS) $(TEST_FILES)
