#!/bin/bash
set -e
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/../ThirdParty/lib
mkdir -p build
rm -rf build/*
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=./cmake/Emscripten.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../
cmake --build .
cd ../