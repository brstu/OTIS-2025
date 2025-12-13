cmake_minimum_required(VERSION 3.14)
project(task_02)

set(CMAKE_CXX_STANDARD 11)

# Основная программа
add_executable(task_02 src/task_02.cpp src/model.cpp)

# Поддиректория с тестами
add_subdirectory(test)