cmake_minimum_required(VERSION 3.5)
project(task_03_ii02720_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)
target_compile_options(${PROJECT_NAME} PRIVATE --coverage -g -O0)
target_link_options(${PROJECT_NAME} PRIVATE --coverage)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
