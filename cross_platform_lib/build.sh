################
# Modified from google/filament with Apache License 2.0
# License link: https://github.com/google/filament/blob/master/LICENSE
#
# Changes:
#  Modify options for this project usage
################

#!/bin/bash
set -e

# Functions definition
function print_help {
    local self_name=`basename $0`
    echo "Usage:"
    echo "    $self_name [options] <build_type1> [<build_type2> ...]"
    echo ""
    echo "Notice:"
    echo "    Currently only support Mac as host build machine"
    echo ""
    echo "Options:"
    echo "    -h"
    echo "        Print this help message."
    echo "    -c"
    echo "        Clean build and Product directories."
    echo "    -j"
    echo "        Do not compile desktop Java projects"
    echo "    -m"
    echo "        Compile with make instead of ninja."
    echo "    -p platform1,platform2,..."
    echo "        Where platformN is [ios|android|web|mac|all]."
    echo "        Platform(s) to build, defaults to mac."
    echo "        Building for iOS will automatically generate / download"
    echo "        the toolchains if needed and perform a partial desktop build."
    echo "    -u"
    echo "        Run all unit tests, default is debug build."
    echo "    -t"
    echo "        Build without test."
    echo "    -v"
    echo "        Add Vulkan support to the Android build."
    echo "    -s"
    echo "        Add iOS simulator support to the iOS build."
    echo "    -w"
    echo "        Build Web documents (compiles .md.html files to .html)."
    echo ""
    echo "Build types:"
    echo "    release"
    echo "        Release build only"
    echo "    debug"
    echo "        Debug build only"
    echo ""
    echo "Examples:"
    echo "    Mac release build:"
    echo "        \$ ./$self_name release"
    echo ""
    echo "    Mac debug and release builds:"
    echo "        \$ ./$self_name debug release"
    echo ""
    echo "    Build without test:"
    echo "        \$ ./$self_name -t debug"
    echo ""
    echo "    Clean build directories:"
    echo "        \$ ./$self_name -c"
    echo ""
    echo "    Android release build type:"
    echo "        \$ ./$self_name -p android release"
    echo ""
    echo "    Multiple build type:"
    echo "        \$ ./$self_name -p ios,android release"
    echo ""
    echo "    Run unit tests mac use debug and release build:"
    echo "        \$ ./$self_name -u release"
    echo ""
}

function build_clean {
    echo "Cleaning build and Product directories..."
    rm -Rvf build
    rm -Rvf Product
}

function build_desktop_target {
    local lc_target=`echo $1 | tr '[:upper:]' '[:lower:]'`

    echo "Building $lc_target in build/mac-${lc_target}..."
    mkdir -p build/mac-${lc_target}

    cd build/mac-${lc_target}

    if [[ ! -d "CMakeFiles" ]] || [[ "$ISSUE_CMAKE_ALWAYS" == "true" ]]; then
        if [[ "$BUILD_TESTS" == "true" ]]; then
            cmake \
                -G "$BUILD_GENERATOR" \
                -DCMAKE_BUILD_TYPE=$1 \
                -DBUILD_TEST=ON \
                -DCMAKE_INSTALL_PREFIX=../../Product/mac/${lc_target}/ \
                ../..
        else
            cmake \
                -G "$BUILD_GENERATOR" \
                -DCMAKE_BUILD_TYPE=$1 \
                -DBUILD_TEST=OFF \
                -DCMAKE_INSTALL_PREFIX=../../Product/mac/${lc_target}/ \
                ../..
        fi
    fi
    
    ${BUILD_COMMAND}

    echo "Installing ${lc_target} in Product/mac/${lc_target}/filament..."
    ${BUILD_COMMAND} install

    cd ../..
}

function build_desktop {
    if [[ "$ISSUE_DEBUG_BUILD" == "true" ]]; then
        echo "Building mac desktop - Debug"
        build_desktop_target "Debug"
    fi

    if [[ "$ISSUE_RELEASE_BUILD" == "true" ]]; then
        echo "Building mac desktop - Release"
        build_desktop_target "Release"
    fi
}

function build_ios {
    if [[ "$ISSUE_DEBUG_BUILD" == "true" ]]; then
        echo "Building ios - Debug"
        # build_desktop_target "Debug" "$1"
    fi

    if [[ "$ISSUE_RELEASE_BUILD" == "true" ]]; then
        echo "Building ios - Release"
        # build_desktop_target "Release" "$1"
    fi
}

function build_android {
    if [[ "$ISSUE_DEBUG_BUILD" == "true" ]]; then
        echo "Building android - Debug"
        # build_desktop_target "Debug" "$1"
    fi

    if [[ "$ISSUE_RELEASE_BUILD" == "true" ]]; then
        echo "Building android - Release"
        # build_desktop_target "Release" "$1"
    fi
}

function build_web {
    if [[ "$ISSUE_DEBUG_BUILD" == "true" ]]; then
        echo "Building web - Debug"
        # build_desktop_target "Debug" "$1"
    fi

    if [[ "$ISSUE_RELEASE_BUILD" == "true" ]]; then
        echo "Building web - Release"
        # build_desktop_target "Release" "$1"
    fi
}

function run_tests {
    if [[ "$ISSUE_DEBUG_BUILD" == "true" ]]; then
        echo "Runing tests - Debug"
        ./build/mac-debug/test/testAll
    fi

    if [[ "$ISSUE_RELEASE_BUILD" == "true" ]]; then
        echo "Runing tests - Release"
        ./build/mac-release/test/testAll
    fi
}

#######################################################
# Script start
ISSUE_CLEAN=false

ISSUE_DEBUG_BUILD=false
ISSUE_RELEASE_BUILD=false

ISSUE_ANDROID_BUILD=flase
ISSUE_IOS_BUILD=flase
ISSUE_MAC_BUILD=true
ISSUE_WEB_BUILD=flase

IOS_BUILD_SIMULATOR=false
BUILD_TESTS=true
RUN_TESTS=false

BUILD_GENERATOR=Ninja
BUILD_COMMAND=ninja

while getopts ":hcjmp:utvsw" opt; do
    case ${opt} in
        h)
            print_help
            exit 1
            ;;
        c)
            ISSUE_CLEAN=true
            ;;
        j)
            ENABLE_JAVA=OFF
            ;;
        m)
            BUILD_GENERATOR="Unix Makefiles"
            BUILD_COMMAND="make"
            ;;
        p)
            ISSUE_MAC_BUILD=false
            platforms=$(echo "$OPTARG" | tr ',' '\n')
            for platform in ${platforms}
            do
                case ${platform} in
                    ios)
                        ISSUE_IOS_BUILD=true
                    ;;
                    android)
                        ISSUE_ANDROID_BUILD=true
                    ;;
                    web)
                        ISSUE_WEB_BUILD=true
                    ;;
                    mac)
                        ISSUE_MAC_BUILD=true
                    ;;
                    all)
                        ISSUE_ANDROID_BUILD=true
                        ISSUE_IOS_BUILD=true
                        ISSUE_MAC_BUILD=true
                        ISSUE_WEB_BUILD=false
                    ;;
                esac
            done
            ;;
        t)
            BUILD_TESTS=false
            ;;
        u)
            ISSUE_DEBUG_BUILD=true
            RUN_TESTS=true
            ;;
        v)
            VULKAN_ANDROID_OPTION="-DFILAMENT_SUPPORTS_VULKAN=ON"
            echo "Enabling support for Vulkan in the core Filament library."
            echo ""
            echo "To switch your application to Vulkan, in Android Studio go to "
            echo "File > Settings > Build > Compiler. In the command-line options field, "
            echo "add -Pextra_cmake_args=-DFILAMENT_SUPPORTS_VULKAN=ON."
            echo "Also be sure to pass Engine.Backend.VULKAN to Engine.create."
            echo ""
            ;;
        s)
            IOS_BUILD_SIMULATOR=true
            echo "iOS simulator support enabled."
            ;;
        w)
            ISSUE_WEB_DOCS=true
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            echo ""
            print_help
            exit 1
            ;;
        :)
            echo "Option -$OPTARG requires an argument." >&2
            echo ""
            print_help
            exit 1
            ;;
    esac
done

if [[ "$#" == "0" ]]; then
    print_help
    exit 1
fi

shift $(($OPTIND - 1))

for arg; do
    if [[ "$arg" == "release" ]]; then
        ISSUE_RELEASE_BUILD=true
    elif [[ "$arg" == "debug" ]]; then
        ISSUE_DEBUG_BUILD=true
    fi
done

mkdir -p build
mkdir -p Product

if [[ "$ISSUE_CLEAN" == "true" ]]; then
    build_clean
else
    if [[ "$ISSUE_MAC_BUILD" == "true" ]]; then
        build_desktop
    fi

    if [[ "$ISSUE_ANDROID_BUILD" == "true" ]]; then
        build_android
    fi

    if [[ "$ISSUE_IOS_BUILD" == "true" ]]; then
        build_ios
    fi

    if [[ "$ISSUE_WEB_BUILD" == "true" ]]; then
        build_web
    fi

    if [[ "$RUN_TESTS" == "true" ]]; then
        run_tests
    fi
fi

