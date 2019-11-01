#!/bin/bash
set -e
mkdir -p build/SDL
rm -rf build/SDL/*
pushd build/SDL
cmake -DCMAKE_TOOLCHAIN_FILE=../../../cmake/Emscripten.cmake -DCMAKE_INSTALL_PREFIX=../../ -DCMAKE_INSTALL_RPATH=../../ ../../src/SDL || exit 1
cmake --build . --config release --target install
echo "Completed build of SDL2"
popd
