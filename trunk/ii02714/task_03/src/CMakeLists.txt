cmake_minimum_required (VERSION 4.2)
project(otis3 LANGUAGES CXX)


add_executable(otis3 
	./otis3.cpp
	)

add_library(linear 
	./linear.h
	)

add_library(PID 
	./PID.h
	)

add_executable(OTIS3
	./otis3.cpp
	)