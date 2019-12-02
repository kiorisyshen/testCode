add_library(pubCppLib pubCppLib.cpp)
target_link_libraries(pubCppLib cppLib)

if(BUILD_TEST)
    target_link_libraries(pubCppLib unitTest)
endif(BUILD_TEST)


install(TARGETS pubCppLib)
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})