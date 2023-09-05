#!/bin/bash
set -ex
~/opt/cheerp/bin/clang -c simple_rt.c -o simple_rt.bc -target cheerp-wasm -g3 -Og
~/opt/cheerp/bin/llvm-link -o libsimplert.bc simple_rt.bc
