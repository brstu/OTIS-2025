cmake_minimum_required(VERSION 3.10)
project(task_02)

set(CMAKE_CXX_STANDARD 11)

# Проверяем наличие googletest
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/googletest")
    message(FATAL_ERROR "Google Test not found. Please clone googletest in the project root.")
endif()

# Настройки для Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

# Добавляем Google Test
add_subdirectory(googletest)

# Основная программа
add_executable(task_02 src/task_02.cpp src/model.cpp)

# Поддиректория с тестами (используем ваше имя ii02710)
add_subdirectory(test)