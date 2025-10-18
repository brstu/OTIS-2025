cmake_minimum_required(VERSION 3.16...3.31)
project(task_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(main otis_task_02.cpp test.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/extern/googletest)

enable_testing()


add_executable(runTests ../test/test_test.cpp test.cpp)
target_link_libraries(runTests gtest gtest_main pthread)
target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME runTests COMMAND runTests)
