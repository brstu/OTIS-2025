cmake_minimum_required(VERSION 3.16)

project(gtest_program)

if(WIN32 AND EXISTS "D:/LABS/vcpkg/scripts/buildsystems/vcpkg.cmake")
    include("D:/LABS/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

add_executable(program ../../task_01/src/model.cpp ../../task_01/src/main.h ../../task_01/src/main.cpp)

enable_testing()

add_executable(gtest_program ../../task_01/src/model.cpp ../../task_01/src/main.h ../test/test.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

target_link_libraries(gtest_program PRIVATE gtest gtest_main)
add_test(NAME all_test COMMAND gtest_program)