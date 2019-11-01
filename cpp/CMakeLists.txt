cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)

project (test)

find_package( OpenCV REQUIRED )

FILE(GLOB TESTSRC *.hpp *.cpp)
add_executable(test ${TESTSRC})
target_link_libraries( test ${OpenCV_LIBS} )