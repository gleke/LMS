cmake_minimum_required(VERSION 3.7)
project(LMS)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(src)

set(SOURCE_FILES test/test.cpp src/LMS.h src/Adaptive_Filter.h src/math_.h)
add_executable(LMS ${SOURCE_FILES})