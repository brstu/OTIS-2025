cmake_minimum_required(VERSION 3.10)
project(otis_task_02)

set(CMAKE_CXX_STANDARD 17)

# Google Test
enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

# Основная программа
add_executable(otis_task_02
    otis_task_02.cpp
    test.cpp
)

# Тесты
add_executable(run_tests
    ../test/test_test.cpp
    test.cpp
)

target_link_libraries(run_tests PRIVATE GTest::GTest GTest::Main)
add_test(NAME run_tests COMMAND run_tests)
