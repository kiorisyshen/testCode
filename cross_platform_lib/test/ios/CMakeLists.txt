#see https://github.com/forexample/testapp

set(CMAKE_OSX_SYSROOT "iphoneos")
set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(APP_HEADER_FILES
    ./AppDelegate.h
    ./ViewController.h
)

set(APP_SOURCE_FILES
    ./AppDelegate.m
    ./ViewController.mm
    ./main.m
)

set(
    STORYBOARDS
    Main.storyboard
)

add_executable(
    testMain_ios
    MACOSX_BUNDLE
    ${APP_HEADER_FILES}
    ${APP_SOURCE_FILES}
)



set_target_properties(
    testMain_ios
    PROPERTIES
    MACOSX_BUNDLE YES
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/plist.in"
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
    RESOURCE "${STORYBOARDS}"
)

set_target_properties(
    testMain_ios
    PROPERTIES
    XCODE_ATTRIBUTE_PRODUCT_NAME
    "testMain_ios"
    XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER
    "com.djij-solution.testMain_ios"
)

target_link_libraries(testMain_ios
    # "-framework CoreGraphics"
    "-framework Foundation"
    "-framework UIKit"
)
