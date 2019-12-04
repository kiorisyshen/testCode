# use OBJECT to final create combined static library
# https://cmake.org/pipermail/cmake/2018-September/068263.html
add_library(cppLib OBJECT
    cppLib.hpp
    cppLib.cpp
)

add_subdirectory(RHI)