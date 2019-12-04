set -e
set -x

mkdir -p build
rm -rf build/*

cd build
cmake -GXcode -DCMAKE_SYSTEM_NAME=iOS ..

open *.xcodeproj