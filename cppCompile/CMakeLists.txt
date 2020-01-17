cmake_minimum_required (VERSION 3.15)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

project (cppCompile)

set(LIB_TYPE OBJECT)
# set(LIB_TYPE STATIC)

add_library(libA ${LIB_TYPE}
    A.hpp
    A.cpp
)
add_library(libB ${LIB_TYPE}
    B.hpp
    B.cpp
)

add_executable(cppCompile main.cpp)
target_link_libraries(cppCompile libA libB)