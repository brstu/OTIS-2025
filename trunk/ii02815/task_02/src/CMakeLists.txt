cmake_minimum_required(VERSION 3.5)
project(model_main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")

add_library(model STATIC model.cpp)

add_executable(ii02815_task_02_main main.cpp)
target_link_libraries(ii02815_task_02_main model)