set(MACOSX_FRAMEWORK_IDENTIFIER "com.dji.gspro.3dengine")
set(MACOSX_FRAMEWORK_NAME "pubCppLib")    
set(MACOSX_FRAMEWORK_BUNDLE_VERSION "1.0.0")    
set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING "1.0.0")
set(CMAKE_OSX_DEPLOYMENT_TARGET "9.3" CACHE STRING "Minimum deployment version")

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
    target_link_libraries(${MACOSX_FRAMEWORK_NAME} PUBLIC unitTest)
endif(BUILD_TEST)

set_target_properties(${MACOSX_FRAMEWORK_NAME} PROPERTIES
    FRAMEWORK TRUE
    FRAMEWORK_VERSION C
    MACOSX_FRAMEWORK_IDENTIFIER ${MACOSX_FRAMEWORK_IDENTIFIER}
    MACOSX_FRAMEWORK_INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/Info.plist.in
    # Mark which headers should public
    PUBLIC_HEADER ${TARGET_HEADERS}
    ## ----------------------------------
    ## Architecture
    ## ----------------------------------
    XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH[variant=Debug] "YES"
    XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH[variant=Release] "NO"
    ## ----------------------------------
    ## Build Location (!!Must see IMPORTANT above)
    ## ----------------------------------
    XCODE_ATTRIBUTE_SYMROOT "${CMAKE_BINARY_DIR}"
    ## ----------------------------------
    ## Build Option
    ## ----------------------------------
    XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Debug] "dwarf"
    XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Release] "dwarf-with-dsym"
    ## ----------------------------------
    ## Deployment
    ## ----------------------------------
    # Enable iPhone,iPad, cmake default is iPhone
    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
    # Enable framework can archive, cmake default is NO
    XCODE_ATTRIBUTE_SKIP_INSTALL "YES"
    XCODE_ATTRIBUTE_INSTALL_PATH "$(LOCAL_LIBRARY_DIR)/Frameworks"
    ## ----------------------------------
    ## Link
    ## ----------------------------------
    XCODE_ATTRIBUTE_DYLIB_INSTALL_NAME_BASE "@rpath"
    XCODE_ATTRIBUTE_LD_DYLIB_INSTALL_NAME "$(DYLIB_INSTALL_NAME_BASE:standardizepath)/$(EXECUTABLE_PATH)"
    XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "$(inherited) @executable_path/Frameworks @loader_path/Frameworks"
    XCODE_ATTRIBUTE_DYLIB_COMPATIBILITY_VERSION "1"
    XCODE_ATTRIBUTE_DYLIB_CURRENT_VERSION "1"
    ## ----------------------------------
    ## Packaging
    ## ----------------------------------
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER ${MACOSX_FRAMEWORK_IDENTIFIER}
    ## ----------------------------------
    ## Apple Clang - Language - C++
    ## ----------------------------------
    XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "gnu++14"
    XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++"
    ## ----------------------------------
    ## Apple Clang - Language - Modules
    ## ----------------------------------
    XCODE_ATTRIBUTE_CLANG_ENABLE_MODULES "YES"
    ## ----------------------------------
    ## Apple Clang - Language - Objective-C
    ## ----------------------------------
    # Enable ARC, cmake default is MRC
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC "YES"
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_WEAK "YES"
    ## ----------------------------------
    ## Apple Clang - Language - Code Generation
    ## ----------------------------------
    XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS "YES"
)
