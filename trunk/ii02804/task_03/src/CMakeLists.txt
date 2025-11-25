cmake_minimum_required(VERSION 3.15)
project(task_03_ii02804)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/pid.cpp
    ${SRC_DIR}/models.cpp
)

# Основная программа
add_executable(task_03_ii02804 ${SRC_FILES})

# Пути для include
target_include_directories(task_03_ii02804 PRIVATE ${SRC_DIR})
