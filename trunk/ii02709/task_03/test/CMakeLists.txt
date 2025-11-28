cmake
cmake_minimum_required(VERSION 3.15)
project(PID_Lab3_Tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP ON  
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(pid_tests_ii02709
    pid_test.cpp
    ../src/pid_controller.cpp
    ../src/model.cpp
)

target_include_directories(pid_tests_ii02709 PRIVATE ../src)

target_link_libraries(pid_tests_ii02709
    GTest::gtest_main
    GTest::gtest
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pid_tests_ii02709 PRIVATE -O0 -g --coverage)
    target_link_options(pid_tests_ii02709 PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(pid_tests_ii02709)