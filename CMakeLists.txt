cmake_minimum_required(VERSION 3.18)
project(testBranch)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
enable_language(Fortran)
set(CMAKE_Fortran_FLAGS_RELEASE  "-O3 -DNDEBUG -ffast-math -march=native ")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -ffast-math -DNDEBUG  -march=native ")
add_executable(testBranch main.cpp)
add_executable(testBilateral_cpp bilateral.cpp)
add_executable(testBilateral_cpp_no_simd bilateral_no_simd.cpp)
add_executable(testBilateral_fortran bilateral.f90)
