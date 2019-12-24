set(LIB_TYPE STATIC)

if(${TARGET_PLATFORM} MATCHES "android")
    # # Android gradle will check library output of .a file anyway,
    # # so here is static library
    # add_library(cppLib STATIC
    #     ${CMAKE_CURRENT_LIST_DIR}/cppLib.hpp
    #     ${CMAKE_CURRENT_LIST_DIR}/cppLib.cpp
    # )
    set(LIB_TYPE STATIC)
else()
    # # use OBJECT to final create combined static library
    # # https://cmake.org/pipermail/cmake/2018-September/068263.html
    # add_library(cppLib OBJECT
    #     ${CMAKE_CURRENT_LIST_DIR}/cppLib.hpp
    #     ${CMAKE_CURRENT_LIST_DIR}/cppLib.cpp
    # )
    set(LIB_TYPE OBJECT)
endif()

add_library(cppLib ${LIB_TYPE}
    ${CMAKE_CURRENT_LIST_DIR}/cppLib.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cppLib.cpp
)

add_subdirectory(RHI)