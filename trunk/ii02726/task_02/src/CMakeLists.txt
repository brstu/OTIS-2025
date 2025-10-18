cmake_minimum_required(VERSION 3.10)
project(task_02)

set(CMAKE_CXX_STANDARD 17)

add_library(task02_lib
    otis_task_02.cpp
    test.cpp
)

target_include_directories(task02_lib PUBLIC .)

add_executable(runTests
    ../test/test_test.cpp
)

target_link_libraries(runTests PRIVATE task02_lib)

enable_testing()
add_test(NAME runTests COMMAND runTests)
