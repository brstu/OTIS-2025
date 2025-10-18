cmake_minimum_required(VERSION 3.10)
project(task_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(main task_02.cpp test.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(runTests ../test/test_test.cpp test.cpp)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)

add_test(NAME runTests COMMAND runTests)
target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})