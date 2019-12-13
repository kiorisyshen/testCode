add_library(pubCppLib STATIC
include/pubCppLib.hpp
pubCppLib.cpp
${PROJECT_SOURCE_DIR}/config.hpp
)
target_link_libraries(pubCppLib cppLib)

if(BUILD_TEST)
    target_link_libraries(pubCppLib unitTest)
endif(BUILD_TEST)


install(TARGETS pubCppLib)
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${PROJECT_SOURCE_DIR}/config.hpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)