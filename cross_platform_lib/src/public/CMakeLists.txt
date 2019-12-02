add_library(pubCppLib pubCppLib.cpp)
target_link_libraries(pubCppLib cppLib)

install(TARGETS pubCppLib)
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})