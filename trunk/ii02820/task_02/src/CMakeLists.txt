cmake_minimum_required(VERSION 3.15)

# Только библиотека
add_library(model_lib STATIC model.cpp)
target_include_directories(model_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Основная программа
add_executable(task_02_main main.cpp)
target_link_libraries(task_02_main model_lib)