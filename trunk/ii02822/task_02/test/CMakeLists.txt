cmake_minimum_required(VERSION 3.14)
project(ThermalModelTests)

find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

add_executable(
    thermal_model_tests
    test_main.cpp
    test_functions.cpp
    ../src/functions.cpp
)

target_link_libraries(
    thermal_model_tests
    GTest::gtest_main
)

target_include_directories(thermal_model_tests PRIVATE ../src)

include(GoogleTest)
gtest_discover_tests(thermal_model_tests)