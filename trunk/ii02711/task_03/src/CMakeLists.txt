project(ii02711_task3
	VERSION 3.5
	LANGUAGES CXX
	)

add_library(Model
	./Model.cpp
	./Model.h
	)

add_executable(ii02711
	./main.cpp
	)

target_link_libraries(ii02711 PRIVATE Model)
