cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)

project(WebAssmbly)

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/algorithm
)

include_directories("${CMAKE_CURRENT_LIST_DIR}/algorithm/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/src")

file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_executable(
    AlgorithmSDK
    ${TARGET_SOURCES}
)

set_target_properties(
    AlgorithmSDK PROPERTIES
    LINK_FLAGS  "--bind --shell-file ${CMAKE_CURRENT_LIST_DIR}/index.html"
)

target_link_libraries(
    AlgorithmSDK
    Algorithm
)

