set(TARGET_HEADERS 
    include/CppLibManager.h
    ${PROJECT_SOURCE_DIR}/config.hpp
)
set(TARGET_SOURCES 
    CppLibManager.cpp
)

add_executable(
    pubCppLib
    ${TARGET_HEADERS}
    ${TARGET_SOURCES}
)

target_link_libraries(
    pubCppLib
    PUBLIC cppLib
)

target_link_options(
    pubCppLib BEFORE
    PUBLIC "--bind"
)

install(TARGETS pubCppLib DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pubCppLib.wasm DESTINATION ${CMAKE_INSTALL_PREFIX})