cmake_minimum_required(VERSION 3.10)

# Название проекта
project(task_03_pid LANGUAGES CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включаем предупреждения (важно для SonarQube)
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ===============================
# Библиотека ПИД-регулятора
# ===============================
add_library(pid
    src/pid.cpp
)

target_include_directories(pid
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ===============================
# Основное приложение
# ===============================
add_executable(pid_app
    src/main.cpp
)

target_link_libraries(pid_app
    PRIVATE
        pid
)

# ===============================
# Google Test
# ===============================
enable_testing()

find_package(GTest REQUIRED)

add_executable(pid_tests
    test/test_pid.cpp
)

target_link_libraries(pid_tests
    PRIVATE
        pid
        GTest::GTest
        GTest::Main
)

add_test(
    NAME PIDTests
    COMMAND pid_tests
)