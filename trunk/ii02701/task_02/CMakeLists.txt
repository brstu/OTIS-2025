cmake_minimum_required(VERSION 3.20)
project(task_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mylib src/model.cpp)
target_include_directories(mylib PUBLIC include)

add_executable(my_app src/main.cpp)
target_link_libraries(my_app PRIVATE mylib)

enable_testing()
add_subdirectory(test)
