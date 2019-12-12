# Create android library target
# Comment:
# Even tough header files can not be compiled
# They should add here for AndroidStudio
add_library(
    CppLibManager SHARED
    ${CMAKE_CURRENT_LIST_DIR}/CppLibManager_jni.h
    ${CMAKE_CURRENT_LIST_DIR}/CppLibManager_jni.cpp
)

# Add C++ library as denpendencies
add_dependencies(
    CppLibManager
    cppLib
    OpenGLESRHI
)
if(BUILD_TEST)
    add_dependencies(CppLibManager PUBLIC unitTest)
endif(BUILD_TEST)

# Add C++ library include path for header include
# target_include_directories(
#        AlgorithmSDK
#        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../algorithm/include
# )

# Add link libraries
target_link_libraries(
    CppLibManager
    PUBLIC cppLib
    PUBLIC OpenGLESRHI
    PRIVATE GLESv2
    PRIVATE log
)

if(BUILD_TEST)
    target_link_libraries(CppLibManager PUBLIC unitTest)
endif(BUILD_TEST)