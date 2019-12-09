set(TARGET_HEADERS 
    include/CppLibManager.h
    ${PROJECT_SOURCE_DIR}/config.hpp
)
set(TARGET_SOURCES 
    CppLibManager.cpp
)

set(JAVASCRIPT_SRC
  ${CMAKE_CURRENT_LIST_DIR}/wasmloader.js
)

set(LOPTS "${LOPTS} --bind")
set(LOPTS "${LOPTS} -s LZ4=1")
set(LOPTS "${LOPTS} -s WASM=1")
set(LOPTS "${LOPTS} -s ALLOW_MEMORY_GROWTH=1")
set(LOPTS "${LOPTS} -s FORCE_FILESYSTEM=1")
# set(LOPTS "${LOPTS} -s USE_WEBGL2=1")
set(LOPTS "${LOPTS} -s FULL_ES2=1")
# set(LOPTS "${LOPTS} -s FULL_ES3=1")
foreach (JS_FILENAME ${JAVASCRIPT_SRC})
  set(LOPTS "${LOPTS} --post-js ${JS_FILENAME}")
endforeach()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LOPTS}")

add_executable(
    pubCppLib
    ${TARGET_HEADERS}
    ${TARGET_SOURCES}
)

target_link_libraries(
    pubCppLib
    PUBLIC cppLib
    PUBLIC OpenGLRHI
)

if(BUILD_TEST)
    target_link_libraries(pubCppLib PUBLIC unitTest)
endif(BUILD_TEST)

add_custom_target(basicAssets ALL
        python $ENV{EMSCRIPTEN}/tools/file_packager.py ${CMAKE_BINARY_DIR}/Asset.data 
            --lz4
            --no-heap-copy
            --js-output=${CMAKE_BINARY_DIR}/Asset.preload.js 
            --preload src/code/Asset/Shaders/WebGL
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        VERBATIM
)

# install to Product
install(TARGETS pubCppLib DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pubCppLib.wasm DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_BINARY_DIR}/Asset.preload.js DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_BINARY_DIR}/Asset.data DESTINATION ${CMAKE_INSTALL_PREFIX})

if(BUILD_TEST)
    # install for test
    install(TARGETS pubCppLib DESTINATION ${CMAKE_BINARY_DIR})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pubCppLib.wasm DESTINATION ${CMAKE_BINARY_DIR})
endif(BUILD_TEST)