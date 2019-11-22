file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(
    Algorithm
    ${TARGET_SOURCES}
)

target_include_directories(
    Algorithm
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)