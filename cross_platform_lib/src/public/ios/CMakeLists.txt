set(MACOSX_FRAMEWORK_NAME "pubCppLib")    
set(MACOSX_FRAMEWORK_BUNDLE_VERSION "1.0.0")    
set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING "1.0.0")

find_library(APPLE_UIKit NAMES UIKit)
find_library(APPLE_CoreGraphics NAMES CoreGraphics)

set(TARGET_HEADERS 
    include/CppLibManager.h
)
set(TARGET_SOURCES 
    CppLibManager.mm
)

add_library(
    ${MACOSX_FRAMEWORK_NAME} SHARED
    ${TARGET_HEADERS}
    ${TARGET_SOURCES}
)

target_link_libraries(
    ${MACOSX_FRAMEWORK_NAME}
    PUBLIC cppLib
    PRIVATE ${APPLE_UIKit}
    PRIVATE ${APPLE_CoreGraphics}
)

if(BUILD_TEST)
    target_link_libraries(${MACOSX_FRAMEWORK_NAME} unitTest)
endif(BUILD_TEST)

set_target_properties(${MACOSX_FRAMEWORK_NAME} PROPERTIES
    FRAMEWORK TRUE
    FRAMEWORK_VERSION A
    #   MACOSX_FRAMEWORK_IDENTIFIER com.cmake.dynamicFramework
    #   MACOSX_FRAMEWORK_INFO_PLIST Info.plist
    # "current version" in semantic format in Mach-O binary file
    # VERSION 16.4.0
    # "compatibility version" in semantic format in Mach-O binary file
    # SOVERSION 1.0.0
    PUBLIC_HEADER ${TARGET_HEADERS}

    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC "YES"
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_WEAK "YES"
)

# install(TARGETS ${MACOSX_FRAMEWORK_NAME}
#         FRAMEWORK DESTINATION ${CMAKE_INSTALL_PREFIX}
# )