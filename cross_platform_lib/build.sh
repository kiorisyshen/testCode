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
    echo "    1. Currently only support Mac as host build machine"
    echo "    2. The default build tools is Ninja, use -m to switch to make"
    echo ""
    echo "Options:"
    echo "    -h"
    echo "        Print this help message."
    echo "    -c"
    echo "        Clean build and Product directories."
    echo "    -m"
    echo "        Compile with make instead of ninja."
    echo "    -p platform1,platform2,..."
    echo "        Where platformN is [ios|android|web|desktop|all]."
    echo "        Platform(s) to build, defaults to desktop."
    echo "        Building for iOS will automatically generate / download"
    echo "        the toolchains if needed and perform a partial desktop build."
    echo "    -u"
    echo "        Run all unit tests in desktop platform."
    echo "    -t"
    echo "        Build with test."
    echo "    -s"
    echo "        Add iOS simulator support to the iOS build."
    echo ""
    echo "Build types:"
    echo "    release"
    echo "        Release build only"
    echo "    debug"
    echo "        Debug build only"
    echo ""
    echo "Examples:"
    echo "    Desktop release build:"
    echo "        \$ ./$self_name release"
    echo ""
    echo "    Desktop debug and release builds:"
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
    echo "    Run unit tests desktop use debug and release build:"
    echo "        \$ ./$self_name -u release"
    echo ""
}

function build_clean {
    echo "Cleaning build and Product directories..."
    rm -Rf $PROJECT_ROOT/build/*
    rm -Rf $PROJECT_ROOT/Product/*
}

function build_desktop_target {
    local lc_target=`echo $1 | tr '[:upper:]' '[:lower:]'`

    echo "Building $lc_target in $PROJECT_ROOT/build/desktop-${lc_target}..."
    mkdir -p $PROJECT_ROOT/build/desktop-${lc_target}

    cd $PROJECT_ROOT/build/desktop-${lc_target}

    if [[ ! -d "CMakeFiles" ]]; then
        local flag_build_tests=OFF
        if [[ "$BUILD_TESTS" == "true" ]]; then
            flag_build_tests=ON
        fi

        cmake \
            -G "$BUILD_GENERATOR" \
            -DCMAKE_BUILD_TYPE=$1 \
            -DBUILD_TEST=$flag_build_tests \
            -DCMAKE_INSTALL_PREFIX=$PROJECT_ROOT/Product/desktop/${lc_target}/ \
            -DTARGET_PLATFORM=desktop \
            ../..
    fi
    
    if [[ "$BUILD_COMMAND" != "None" ]]; then
        ${BUILD_COMMAND}

        echo "Installing ${lc_target} in $PROJECT_ROOT/Product/desktop/${lc_target}..."
        ${BUILD_COMMAND} install
    fi

    cd $PROJECT_ROOT
}

function build_ios_target {
    local lc_target=`echo $1 | tr '[:upper:]' '[:lower:]'`

    echo "Building $lc_target in $PROJECT_ROOT/build/ios-${lc_target}..."
    mkdir -p $PROJECT_ROOT/build/ios-${lc_target}

    cd $PROJECT_ROOT/build/ios-${lc_target}

    local product_dir=$PROJECT_ROOT/Product/ios/${lc_target}/
    mkdir -p $product_dir

    if [[ ! -d "CMakeFiles" ]]; then
        local flag_build_tests=OFF
        if [[ "$BUILD_TESTS" == "true" ]]; then
            flag_build_tests=ON
        fi

        local teamids=()
        if [[ "$BUILD_TESTS" == "true" ]]; then
            echo "============================="
            local certificate=$(xcrun security find-certificate -a -c "iPhone" -p | openssl x509 -text | grep "Subject:")
            echo $certificate

            for item in $(echo $certificate | tr "," "\n")
            do
                if [[ $item == OU* ]]; then
                    teamids+=($(echo $item| cut -d'=' -f 2))
                fi
            done
            echo "============================="
            echo "Please select your team id:"
            for i in "${!teamids[@]}"; do
                printf '%s) %s\n' "$i" "${teamids[i]}"
            done

            read teamidx

            echo "Selected certificate team id: ${teamids[$teamidx]}"
            echo "============================="

            cmake \
            -G "$BUILD_GENERATOR" \
            -DCMAKE_BUILD_TYPE=$1 \
            -DBUILD_TEST=$flag_build_tests \
            -DCMAKE_INSTALL_PREFIX=$product_dir \
            -DCMAKE_SYSTEM_NAME=iOS \
            -DTARGET_PLATFORM=ios \
            -DCMAKE_OSX_DEPLOYMENT_TARGET=9.3 \
            -DCMAKE_IOS_INSTALL_COMBINED=YES \
            "-DCMAKE_OSX_ARCHITECTURES=armv7;armv7s;arm64;x86_64" \
            -DDEVELOPMENT_TEAM_ID=${teamids[$teamidx]} \
            ../..
        else
            cmake \
            -G "$BUILD_GENERATOR" \
            -DCMAKE_BUILD_TYPE=$1 \
            -DBUILD_TEST=$flag_build_tests \
            -DCMAKE_INSTALL_PREFIX=$product_dir \
            -DCMAKE_SYSTEM_NAME=iOS \
            -DTARGET_PLATFORM=ios \
            -DCMAKE_OSX_DEPLOYMENT_TARGET=9.3 \
            -DCMAKE_IOS_INSTALL_COMBINED=YES \
            "-DCMAKE_OSX_ARCHITECTURES=armv7;armv7s;arm64;x86_64" \
            ../..
        fi
    fi
    
    if [[ "$BUILD_COMMAND" != "None" ]] && [[ "$BUILD_TESTS" == "false" ]]; then
        cmake --build . --config $1 --target install
    fi

    cd $PROJECT_ROOT
}

function build_desktop {
    if [[ "$ISSUE_DEBUG_BUILD" == "true" ]]; then
        echo "Building desktop - Debug"
        build_desktop_target "Debug"
    fi

    if [[ "$ISSUE_RELEASE_BUILD" == "true" ]]; then
        echo "Building desktop - Release"
        build_desktop_target "Release"
    fi
}

function build_ios {
    if [[ "$ISSUE_DEBUG_BUILD" == "true" ]]; then
        echo "Building ios - Debug"
        build_ios_target "Debug"
    fi

    if [[ "$ISSUE_RELEASE_BUILD" == "true" ]]; then
        echo "Building ios - Release"
        build_ios_target "Release"
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
        $PROJECT_ROOT/build/desktop-debug/platformTest/desktop/unitTestMain
    fi

    if [[ "$ISSUE_RELEASE_BUILD" == "true" ]]; then
        echo "Runing tests - Release"
        $PROJECT_ROOT/build/desktop-release/platformTest/desktop/unitTestMain
    fi
}

#######################################################
# Script start
ISSUE_CLEAN=false

ISSUE_DEBUG_BUILD=false
ISSUE_RELEASE_BUILD=false

ISSUE_ANDROID_BUILD=flase
ISSUE_IOS_BUILD=flase
ISSUE_DESKTOP_BUILD=true
ISSUE_WEB_BUILD=flase

IOS_BUILD_SIMULATOR=false
BUILD_TESTS=false
RUN_TESTS=false

BUILD_GENERATOR=Ninja
BUILD_COMMAND=ninja

PROJECT_ROOT="$(pwd)"

while getopts ":hcmp:uts" opt; do
    case ${opt} in
        h)
            print_help
            exit 1
            ;;
        c)
            ISSUE_CLEAN=true
            ;;
        m)
            BUILD_GENERATOR="Unix Makefiles"
            BUILD_COMMAND="make"
            ;;
        p)
            ISSUE_DESKTOP_BUILD=false
            platforms=$(echo "$OPTARG" | tr ',' '\n')
            for platform in ${platforms}
            do
                case ${platform} in
                    ios)
                        ISSUE_IOS_BUILD=true
                        BUILD_GENERATOR=Xcode
                        BUILD_COMMAND=xcodebuild
                    ;;
                    android)
                        ISSUE_ANDROID_BUILD=true
                    ;;
                    web)
                        ISSUE_WEB_BUILD=true
                    ;;
                    desktop)
                        ISSUE_DESKTOP_BUILD=true
                    ;;
                    all)
                        ISSUE_ANDROID_BUILD=true
                        ISSUE_IOS_BUILD=true
                        ISSUE_DESKTOP_BUILD=true
                        ISSUE_WEB_BUILD=false
                    ;;
                esac
            done
            ;;
        t)
            BUILD_TESTS=true
            ;;
        u)
            RUN_TESTS=true
            ;;
        s)
            IOS_BUILD_SIMULATOR=true
            echo "iOS simulator support enabled."
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

mkdir -p $PROJECT_ROOT/build
mkdir -p $PROJECT_ROOT/Product

if [[ "$ISSUE_CLEAN" == "true" ]]; then
    build_clean
    echo ""
fi

if [[ "$ISSUE_DESKTOP_BUILD" == "true" ]]; then
    build_desktop
    echo ""
fi

if [[ "$ISSUE_ANDROID_BUILD" == "true" ]]; then
    build_android
    echo ""
fi

if [[ "$ISSUE_IOS_BUILD" == "true" ]]; then
    build_ios
    echo ""
fi

if [[ "$ISSUE_WEB_BUILD" == "true" ]]; then
    build_web
    echo ""
fi

if [[ "$RUN_TESTS" == "true" ]]; then
    run_tests
fi

