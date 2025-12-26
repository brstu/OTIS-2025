project(ii02716_task03
	VERSION 3.5
	LANGUAGES CXX
	)

add_library(Model 
	./Equations.cpp
	./Equations.h
	./PID.cpp
	./PID.h
	)

add_executable(PID 
	./otis3s.cpp
	)

target_link_libraries (PID PRIVATE Model)