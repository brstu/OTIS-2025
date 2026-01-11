cmake_minimum_required(VERSION 3.15)
project(model_lib)

# Библиотека
add_library(model_lib STATIC model.cpp)

# Основная программа
add_executable(task_02_main main.cpp)
target_link_libraries(task_02_main model_lib)