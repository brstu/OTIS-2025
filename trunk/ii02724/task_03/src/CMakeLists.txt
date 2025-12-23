project(ii02724_task3
	LANGUAGES CXX
	VERSION 3.5
	)

add_library(PID
	./PID.cpp
	./PID.h
	)

add_executable(ii02724_task3
	./otis3.cpp
	)

target_link_libraries(ii02724_task3 PRIVATE PID)