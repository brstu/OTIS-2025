project(task2_ii02711
        LANGUAGES CXX
	VERSION 3.5
	)

add_library(equat
	equations.cpp
	)

add_executable(otis2 
	main.cpp
	)

target_link_libraries(otis2 PRIVATE equat)