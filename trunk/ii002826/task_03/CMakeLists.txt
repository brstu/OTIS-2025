cmake_minimum_required(VERSION 3.16)
project(task_03_ii002826)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(pid_sim
    src/main.cpp
    src/pid.cpp
    src/model.cpp
)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Тесты
add_executable(pid_tests
    test/test_pid.cpp
    src/pid.cpp
    src/model.cpp
)

target_link_libraries(pid_tests GTest::gtest_main)

add_test(NAME PIDTests COMMAND pid_tests)
