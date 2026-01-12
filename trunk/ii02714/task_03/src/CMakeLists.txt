cmake_minimum_required (VERSION 3.20)
project (task_03_ii02714 LANGUAGES CXX)


add_library(PID_ii02714
	./PID.cpp
	)

add_executable (ii02714 
	./otis3_1.cpp
	)
target_link_libraries(ii02714 PRIVATE PID_ii02714)
