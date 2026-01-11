project(ii02721 
	LANGUAGES CXX
	VERSION 3.5
	)

add_library(Equations
	./n_linear.cpp
	)
add_executable(ii02721
	./otis2.cpp
	)

target_link_libraries(ii02721 PRIVATE Equations)