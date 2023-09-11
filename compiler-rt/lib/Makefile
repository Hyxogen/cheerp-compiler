TARGET := libasan.bc

CXX	:= /home/daan/opt/cheerp/bin/clang++
CXXFLAGS := -O0 -g0 -target cheerp-wasm -I.

LINK_CMD := /home/daan/opt/cheerp/bin/llvm-link

CXX_FILES := \
	     asan_new/asan_rtl.cpp  \
	     asan_new/asan_cheerpwasm.cpp \
	     asan_new/asan_report.cpp \
	     asan_new/asan_globals.cpp

HEADER_DEPS	:= $(CXX_FILES:.cpp=.d)
OBJ_FILES	:= $(CXX_FILES:.cpp=.bc)

$(TARGET): $(OBJ_FILES)
	$(LINK_CMD) -o $@ $(OBJ_FILES)

-include $(HEADER_DEPS)
%.bc: %.cpp Makefile
	$(CXX) -o $@ $< $(CXXFLAGS) -c -MMD

clean:
	rm -f $(OBJ_FILES) $(HEADER_DEPS)
