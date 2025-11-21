cmake_minimum_required (VERSION 3.16)
project(otis3 LANGUAGES CXX)

target_link_libraries(OTIS3 PRIVATE PID linear)

add_library(linear 
	./linear.cpp
	)

add_library(PID 
	./PID.cpp
	)

add_executable(OTIS3
	./otis3.cpp
	)
