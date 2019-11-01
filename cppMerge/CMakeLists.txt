cmake_minimum_required (VERSION 3.1)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

project (test)

add_executable(test test.cpp)
add_executable(test02_Swizzle test02_Swizzle.cpp)
