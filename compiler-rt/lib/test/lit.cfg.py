# -*- Python -*-

import os
import platform
import re
import lit.formats
config.name = 'AddressSanitizer'

cheerp_dest=os.environ['CHEERP_DEST']

config.suffixes = ['.c', '.cpp']
config.test_format = lit.formats.ShTest("0")
config.clang = cheerp_dest + "/bin/clang"
config.clangxx = cheerp_dest + "/bin/clang++"

def build_invocation(compile_flags):
  return " " + " ".join([config.clang] + compile_flags) + " "

def build_cxx_invocation(compile_flags):
  return " " + " ".join([config.clangxx] + compile_flags) + " "

extra_link_flags = []
target_cflags = ["-target cheerp-wasm"] + extra_link_flags
target_cxxflags = target_cflags + extra_link_flags
clang_asan_static_cflags = (["-fsanitize=address"])
clang_asan_static_cxxflags = clang_asan_static_cflags

clang_asan_cflags = clang_asan_static_cflags
clang_asan_cxxflags = clang_asan_static_cxxflags

config.substitutions.append( ("%clang ", build_invocation(target_cflags)) )
config.substitutions.append( ("%clangxx ", build_cxx_invocation(target_cxxflags)) )
config.substitutions.append( ("%clang_asan ", build_invocation(clang_asan_cflags)) )
config.substitutions.append( ("%clangxx_asan ", build_cxx_invocation(clang_asan_cxxflags)) )
config.substitutions.insert(0, ('%run', "node"))
