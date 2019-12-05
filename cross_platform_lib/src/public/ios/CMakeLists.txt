set(MACOSX_FRAMEWORK_IDENTIFIER "com.dji.gspro.3dengine")
set(MACOSX_FRAMEWORK_NAME "pubCppLib")    
set(MACOSX_FRAMEWORK_BUNDLE_VERSION "1.0.0")    
set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING "1.0.0")

# Pack resource with framework
set(SHADER_SOURCES
    testShader
)

if(NOT BUILD_TEST)
    foreach(SHADER
            IN
            LISTS
            SHADER_SOURCES)
        add_custom_command(OUTPUT ${SHADER}.air
                            COMMAND xcrun
                                    -sdk
                                    ${CMAKE_OSX_SYSROOT}
                                    metal
                                    -g
                                    -MO
                                    -c
                                    ${PROJECT_SOURCE_DIR}/src/code/Asset/Shaders/${SHADER}.metal
                                    -o
                                    ${SHADER}.air
                            COMMENT "Compile ${SHADER}.metal --> ${SHADER}.air"
                            DEPENDS ${PROJECT_SOURCE_DIR}/src/code/Asset/Shaders/${SHADER}.metal)
        list(APPEND AIRS ${SHADER}.air)
    endforeach(SHADER)

    add_custom_command(OUTPUT Main.metalar
                        COMMAND xcrun
                                -sdk
                                ${CMAKE_OSX_SYSROOT}
                                metal-ar
                                rcv
                                Main.metalar
                                ${AIRS}
                        COMMENT "Archive ${AIRS} --> Main.metalar"
                        DEPENDS ${AIRS})

    add_custom_command(OUTPUT Main.metallib
                        COMMAND xcrun
                                -sdk
                                ${CMAKE_OSX_SYSROOT}
                                metallib
                                Main.metalar
                                -split-module-without-linking
                                -o
                                Main.metallib
                        COMMENT "Compile Main.metalar --> Main.metallib"
                        DEPENDS Main.metalar)

    set(RESOURCE_FILES
        Main.metallib
    )
else()
    set(RESOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/code/Asset/Shaders/${SHADER_SOURCES}.metal
        CACHE INTERNAL "RESOURCE_FILES"
    )
endif(BUILD_TEST)

find_library(APPLE_UIKit NAMES UIKit)
find_library(APPLE_CoreGraphics NAMES CoreGraphics)

set(TARGET_HEADERS 
    include/CppLibManager.h
    ${PROJECT_SOURCE_DIR}/config.hpp
)
set(TARGET_SOURCES 
    CppLibManager.mm
)

add_library(
    ${MACOSX_FRAMEWORK_NAME} STATIC
    ${TARGET_HEADERS}
    ${TARGET_SOURCES}
    ${RESOURCE_FILES}
)

target_link_libraries(
    ${MACOSX_FRAMEWORK_NAME}
    PUBLIC cppLib
    PUBLIC MetalRHI
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
    PUBLIC_HEADER "${TARGET_HEADERS}"
    ## ----------------------------------
    ## Architecture
    ## ----------------------------------
    XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH[variant=Debug] "NO"
    XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH[variant=Release] "NO"
    ## ----------------------------------
    ## Build Location (!!Must see IMPORTANT above)
    ## ----------------------------------
    # XCODE_ATTRIBUTE_SYMROOT "${CMAKE_BINARY_DIR}"
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
    # XCODE_ATTRIBUTE_SKIP_INSTALL "YES"
    # XCODE_ATTRIBUTE_INSTALL_PATH "$(LOCAL_LIBRARY_DIR)/Frameworks"
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
    RESOURCE "${RESOURCE_FILES}"
)

install(TARGETS ${MACOSX_FRAMEWORK_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX})
