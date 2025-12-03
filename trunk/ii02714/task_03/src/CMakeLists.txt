cmake_minimum_required (VERSION 3.5)
project (task_03_ii02714 LANGUAGES CXX)


add_library(PID 
	./PID.cpp
	)

add_executable (ii002714 
	./otis3_1.cpp
	)
target_link_libraries(ii002714 PRIVATE PID)