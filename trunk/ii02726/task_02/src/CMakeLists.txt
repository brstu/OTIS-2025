cmake_minimum_required(VERSION 3.16)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(task02_lib
    src/otis_task_02.cpp
    src/test.cpp
)

target_include_directories(task02_lib PUBLIC src)

add_executable(runTests test/test_test.cpp)
target_link_libraries(runTests PRIVATE task02_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)
