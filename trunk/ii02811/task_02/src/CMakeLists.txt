cmake_minimum_required(VERSION 3.15.0)

set(VCPKG_TARGET_TRIPLET x64-windows)
include("D:\\LABS\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")

project(gtest_program)

add_executable(program main.cpp model.cpp main.h)
include_directories(include)

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(gtest_program ../test/test.cpp model.cpp main.h)
target_link_libraries(gtest_program PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME all_test COMMAND gtest_program)