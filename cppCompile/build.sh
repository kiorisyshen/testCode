mkdir -p build
rm -rf build/*
cd build
cmake ..
make VERBOSE=1