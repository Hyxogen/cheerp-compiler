#!/bin/bash
~/opt/cheerp/bin/opt < deref.bc > /dev/null -passes=asan -debug 2> out
