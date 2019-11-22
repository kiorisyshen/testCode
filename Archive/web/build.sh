#!/bin/sh

EMSDK_GIT="../emsdk"

if [ -d $EMSDK_GIT ] 
then
    echo "update emsdk"
    $EMSDK_GIT/emsdk update-tags
else
    echo "clone from https://github.com/emscripten-core/emsdk.git "
    git clone https://github.com/emscripten-core/emsdk.git $EMSDK_GIT
    $EMSDK_GIT/emsdk install latest
fi

$EMSDK_GIT/emsdk activate latest

rm -rf build        && \
mkdir build         && \
cd build            && \
cmake ../WebAssembly/.
