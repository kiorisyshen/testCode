cmake_minimum_required (VERSION 3.1)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

project (test)

# add_executable(test test.cpp)
# add_executable(test02_Swizzle test02_Swizzle.cpp)

add_executable(test03_Eigen test03_Eigen.cpp)
add_executable(test04_Memory test04_Memory.cpp)
add_executable(test05_UUID test05_UUID.cpp)
add_executable(test06_GeomMath test06_GeomMath.cpp)
add_executable(test07_Enum test07_Enum.cpp)
add_executable(test08_Misc test08_Misc.cpp)