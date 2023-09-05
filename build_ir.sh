#!/bin/bash
set -ex
~/opt/cheerp/bin/clang -S deref.c -emit-llvm -target cheerp-wasm -fsanitize=address
