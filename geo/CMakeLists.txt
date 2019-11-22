cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)

project (geo)

FILE(GLOB TESTSRC *.h *.cpp)
add_executable(geo ${TESTSRC})