cmake_minimum_required(VERSION 3.5)
project(ii02721_task03
	LANGUAGES CXX
	)

add_library(PID
	./PID.cpp
	./Model.cpp
	)

add_executable(ii02721_task03
	./main.cpp
	)

target_link_libraries(ii02721_task03 PRIVATE PID)

