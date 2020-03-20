cmake_minimum_required (VERSION 3.1)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

project (interpreter)

add_executable(testVM testVM.cpp VM.hpp VM.cpp Driver.hpp)