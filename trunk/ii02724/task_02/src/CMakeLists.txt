cmake_minimum_required (VERSION 3.5)
project (task_02_ii02724)

add_library(linear 
		linear.cpp)

add_library(nonlinear 
		Nonlinear.cpp)

add_executable (ii02724 
		otis2.cpp)

target_link_libraries(ii02724 PRIVATE linear)
target_link_libraries(ii02724 PRIVATE nonlinear)