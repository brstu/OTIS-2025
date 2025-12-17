cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# Поиск GTest
find_package(GTest REQUIRED)

include_directories(include)

add_library(calculator src/calculator.cpp)

add_executable(run_tests tests/test_calculator.cpp)
target_link_libraries(run_tests calculator GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)