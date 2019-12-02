
if(BUILD_TEST)
    add_executable(unitTestMain unitTestMain.cpp)
    target_link_libraries(unitTestMain pubCppLib)
endif(BUILD_TEST)

add_executable(debugMain debugMain.cpp)
target_link_libraries(debugMain pubCppLib)