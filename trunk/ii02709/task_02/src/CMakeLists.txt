cmake_minimum_required(VERSION 3.5)
project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lab2 STATIC lab2.cpp)
target_include_directories(lab2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main_exec main.cpp)
target_link_libraries(main_exec PRIVATE lab2)