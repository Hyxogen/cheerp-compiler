#!/bin/bash
set -ex
~/opt/cheerp/bin/clang -target cheerp-wasm deref.c libsimplert.bc -cheerp-pretty-code -fsanitize=address -v -save-temps=obj -O0 -cheerp-no-lto
#~/opt/cheerp/bin/clang -target cheerp-wasm deref.c libasan.bc -cheerp-pretty-code -fsanitize=address -v -save-temps=obj -O0 -cheerp-no-lto
