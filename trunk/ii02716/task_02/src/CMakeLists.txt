project(task2_ii02716
        LANGUAGES CXX
	VERSION 3.5
	)

add_library(Systems
	./LinearSystem.cpp
	./NonLinearSystem.cpp
	./Simulator.cpp
	)

add_executable(otis2_ii02716 
	./main.cpp
	)

target_link_libraries(otis2_ii02716 PRIVATE Systems)