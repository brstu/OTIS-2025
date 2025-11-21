cmake_minimum_required (VERSION 4.2)
project(otis3 LANGUAGES CXX)


add_library(linear 
	./linear.cpp
	)

add_library(PID 
	./PID.cpp
	)

add_executable(OTIS3
	./otis3.cpp
	)