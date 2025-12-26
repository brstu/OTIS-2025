cmake_minimum_required(VERSION 3.16)
project(task_03_ii002826)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# 1. Основной исполняемый файл
#
add_executable(pid_simen
    main.cpp
    pid.cpp
    model.cpp
)

#
# 2. GoogleTest
#
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

#
# 3. Модульные тесты
#
add_executable(pid_testes
    ../test/test_pid.cpp
    pid.cpp
    model.cpp
)

target_link_libraries(pid_testes
    GTest::gtest_main
)

add_test(NAME PIDTests COMMAND pid_testes)
