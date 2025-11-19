cmake_minimum_required(VERSION 3.5)

project(task_03_ii02807_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Добавляем путь к заголовкам src
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_executable(task_03_ii02807_test
    test.cpp
    ../src/pid.cpp
    ../src/model.cpp
)

target_link_libraries(task_03_ii02807_test PRIVATE gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(task_03_ii02807_test)
