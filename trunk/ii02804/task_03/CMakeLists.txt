cmake_minimum_required(VERSION 3.16)
project(task_03_pid)

set(CMAKE_CXX_STANDARD 17)

add_library(models src/models.cpp src/models.h)
add_library(pid src/pid.cpp src/pid.h)

add_executable(simulator src/main.cpp)
target_link_libraries(simulator PRIVATE models pid)

# --- GoogleTest ---
enable_testing()
find_package(GTest REQUIRED)

add_executable(test_pid test/test_pid.cpp)
target_link_libraries(test_pid PRIVATE GTest::gtest_main pid models)

include(GoogleTest)
gtest_discover_tests(test_pid)
