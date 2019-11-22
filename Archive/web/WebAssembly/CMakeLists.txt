cmake_minimum_required(VERSION 3.14)

set(EMSCRIPTEN_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../../emsdk/upstream/emscripten)
set(CMAKE_TOOLCHAIN_FILE ${EMSCRIPTEN_ROOT_PATH}/cmake/Modules/Platform/Emscripten.cmake)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../../algorithm
    ${CMAKE_CURRENT_BINARY_DIR}/algorithm
)

project(WebAssmbly)

file(GLOB_RECURSE TARGET_HEADERS ${CMAKE_CURRENT_LIST_DIR}/src/*.h)
file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_executable(
    AlgorithmSDK
    ${TARGET_HEADERS}
    ${TARGET_SOURCES}
)

add_dependencies(
    AlgorithmSDK
    Algorithm
)

target_include_directories(
        AlgorithmSDK
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../algorithm/include
        PUBLIC ${EMSCRIPTEN_ROOT_PATH}/upstream/emscripten/system/include
)


set_target_properties(
    AlgorithmSDK PROPERTIES
    LINK_FLAGS  "--bind -s WASM=1 --shell-file ${CMAKE_CURRENT_LIST_DIR}/index.html"
)

target_link_libraries(
    AlgorithmSDK
    Algorithm
)

