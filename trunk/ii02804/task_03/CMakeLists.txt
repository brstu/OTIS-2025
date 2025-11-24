cmake_minimum_required(VERSION 3.16)
project(task_03_pid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Библиотеки проекта ---
add_library(models src/models.cpp src/models.h)
add_library(pid src/pid.cpp src/pid.h)

target_include_directories(models PUBLIC src)
target_include_directories(pid PUBLIC src)

# --- Исполняемый файл симулятора ---
add_executable(simulator src/main.cpp)
target_link_libraries(simulator PRIVATE models pid)
target_include_directories(simulator PRIVATE src)

# --- GoogleTest ---
enable_testing()
find_package(GTest REQUIRED)

add_executable(test_pid test/test_pid.cpp)
# Сначала свои библиотеки, потом GTest
target_link_libraries(test_pid PRIVATE pid models GTest::gtest_main)
target_include_directories(test_pid PRIVATE src)

# Автоматическое обнаружение тестов GoogleTest
include(GoogleTest)
gtest_discover_tests(test_pid)
