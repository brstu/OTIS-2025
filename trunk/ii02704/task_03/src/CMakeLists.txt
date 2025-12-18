project(ii02704_task3
	LANGUAGES CXX
	VERSION 3.5
	)

add_library(PID
	./PID.cpp
	./PID.h
	)

add_executable(ii02704_task3
	./main.cpp
	)

target_link_libraries(ii02704_task3 PRIVATE PID)