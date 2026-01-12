cmake_minimum_required(VERSION 3.15)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(lab3_ii02816 main_lab3.cpp pid.cpp mdl.cpp)

# Тестовая программа
add_executable(test_runner ../test/testlab_3.cpp pid.cpp mdl.cpp)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(test_runner gtest_main)

# Простой тест вместо gtest_discover_tests
enable_testing()
add_test(NAME lab3_tests COMMAND test_runner)

add_executable(lab3_ii02816
    main_lab3.cpp
    plot_utils.cpp  # файл с реализацией generatePythonPlotScript
)