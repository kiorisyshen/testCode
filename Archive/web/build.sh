#!/bin/sh
set -e

mkdir -p build
rm -rf build/*
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../../../wasm/cmake/Emscripten.cmake ../WebAssembly/.
cmake --build . -v
cd -
