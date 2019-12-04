set(MACOSX_TESTAPP_NAME "iosTestMain")
set(MACOSX_TESTAPP_IDENTIFIER "com.dji.gspro.3dengine.test")

find_library(MTK_LIBRARY MetalKit required)
find_library(METAL_LIBRARY Metal required)

set(
    SOURCES
    sources/AppDelegate.h
    sources/AppDelegate.m
    sources/ViewController.h
    sources/ViewController.m
    sources/main.m
)

set(
    STORYBOARDS
    storyboards/Main.storyboard
    storyboards/LaunchScreen.storyboard
)

add_executable(
    ${MACOSX_TESTAPP_NAME}
    ${SOURCES}
    ${STORYBOARDS}
)

add_dependencies(
    ${MACOSX_TESTAPP_NAME}
    pubCppLib
)

set_target_properties(
    ${MACOSX_TESTAPP_NAME}
    PROPERTIES
    MACOSX_BUNDLE YES
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/Info.plist"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
    XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${DEVELOPMENT_TEAM_ID}"
    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_WEAK "YES"
    # XCODE_ATTRIBUTE_INSTALL_PATH "${CMAKE_BINARY_DIR}/ProductRelease"
    # XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES "NO"
    RESOURCE "${STORYBOARDS}"
)

set_target_properties(
    ${MACOSX_TESTAPP_NAME}
    PROPERTIES
    XCODE_ATTRIBUTE_PRODUCT_NAME
    "${MACOSX_TESTAPP_NAME}"
    XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER
    "${MACOSX_TESTAPP_IDENTIFIER}"
)

target_link_libraries(
    ${MACOSX_TESTAPP_NAME}
    "-framework CoreGraphics"
    "-framework Foundation"
    "-framework UIKit"
    pubCppLib
    ${MTK_LIBRARY}
    ${METAL_LIBRARY}
)