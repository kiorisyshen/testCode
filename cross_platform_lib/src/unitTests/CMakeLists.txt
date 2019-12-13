add_library(unitTest STATIC
    unitTest.hpp
    unitTest.cpp
)

target_link_libraries(unitTest
    PUBLIC cppLib
)