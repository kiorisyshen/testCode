cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)

project(Algorithm)

file(GLOB_RECURSE TARGET_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)


add_library(
    Algorithm
    ${TARGET_HEADERS}
    ${TARGET_SOURCES}
)