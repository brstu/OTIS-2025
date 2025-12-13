cmake_minimum_required (VERSION 3.5)
project (task_02_ii02704)

add_library(linear 
		linear.cpp)

add_executable (ii02704_task2
		otis2.cpp)

target_link_libraries(ii02704_task2 PRIVATE linear)
