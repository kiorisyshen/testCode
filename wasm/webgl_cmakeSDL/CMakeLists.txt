cmake_minimum_required(VERSION 3.1)
project(webglTest)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s FORCE_FILESYSTEM=1 -s LZ4=1 --emrun")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g4 --source-map-base http://localhost:8080/")

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/../ThirdParty/include")

add_executable(testWebGL
main.cpp
BaseApplication.cpp
GraphicsManager.cpp
SdlApplication.cpp
)

# target_link_libraries(testWebGL
#     SDL2::SDL2main
#     SDL2::SDL2
# )

# target_link_libraries(testWebGL)

set_target_properties(testWebGL
PROPERTIES LINK_FLAGS "-s FULL_ES2=1 -s FULL_ES3=1 -s USE_WEBGL2=1 -s USE_SDL=2 -s DEMANGLE_SUPPORT=1"
)