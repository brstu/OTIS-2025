cmake_minimum_required(VERSION 3.10)
project(task_02)

set(CMAKE_CXX_STANDARD 17)

# Main program
add_executable(main
    src/otis_task_02.cpp
    src/test.cpp
)

add_executable(runTests
    test/test_test.cpp
    src/test.cpp
)

target_include_directories(main PRIVATE src)
target_include_directories(runTests PRIVATE src)

enable_testing()
add_test(NAME runTests COMMAND runTests)
