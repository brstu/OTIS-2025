cmake_minimum_required(VERSION 3.16)
project(task_03_ii02814)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

cmake_policy(SET CMP0079 NEW)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(runTests_ii02814 ../tests/test.cpp  module.cpp)

add_executable(main_ii02814 main.cpp module.cpp)
target_compile_options(main_ii02814 PRIVATE -fprofile-arcs -ftest-coverage)
target_link_options(main_ii02814 PRIVATE -fprofile-arcs -ftest-coverage)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(runTests_ii02814 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(runTests_ii02814 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )
endif()

target_link_libraries(runTests_ii02814 gtest gtest_main)

target_include_directories(runTests_ii02814 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(runTests_ii02814)