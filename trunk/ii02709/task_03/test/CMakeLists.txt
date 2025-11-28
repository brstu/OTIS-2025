cmake_minimum_required(VERSION 3.14)
project(PID_Tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Куда класть exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(pid_tests
    pid_test.cpp
    ../src/pid_controller.cpp
    ../src/model.cpp
)

target_include_directories(pid_tests PRIVATE ../src)
target_link_libraries(pid_tests GTest::gtest_main GTest::gtest)

# === ДЛЯ ПОКРЫТИЯ (gcov) ===
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pid_tests PRIVATE --coverage -g -O0)
    target_link_options(pid_tests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(pid_tests)