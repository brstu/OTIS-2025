project(ii02722_task03
	VERSION 3.10
	LANGUAGES CXX
	)

add_library(Model_ii02722
	./Model.cpp
	)

add_executable(PID_ii02722
	./ii02722.cpp
	)

target_link_libraries(PID_ii02722 Model_ii02722)