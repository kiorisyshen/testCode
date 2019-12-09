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
set(LOPTS "${LOPTS} -s ALLOW_MEMORY_GROWTH=1")
set(LOPTS "${LOPTS} -s USE_WEBGL2=1")
# set(LOPTS "${LOPTS} -s FULL_ES2=1")
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

install(TARGETS pubCppLib DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pubCppLib.wasm DESTINATION ${CMAKE_INSTALL_PREFIX})