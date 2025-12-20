cmake_minimum_required(VERSION 3.10)
add_library(pid_lib
    functions.cpp
)

target_include_directories(pid_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task_03 main.cpp)
target_link_libraries(task_03 pid_lib)
