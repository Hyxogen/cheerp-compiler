#!/bin/bash
set -ex
~/opt/cheerp/bin/clang++ -c asan/asan_allocator.cpp -o alloc.bc -target cheerp-wasm -I. -DSANITIZER_CHEERPWASM
~/opt/cheerp/bin/llvm-dis alloc.bc
cat alloc.ll | rg "ret void "
