cmake_minimum_required(VERSION 3.16)
project(task_03_ii02801 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Пути
#
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../test)

include_directories(${SRC_DIR})

#
# Основной executable
#
set(SOURCES
    ${SRC_DIR}/lab3main.cpp
    ${SRC_DIR}/model.cpp
    ${SRC_DIR}/pid.cpp
)

add_executable(task03 ${SOURCES})

#
# GoogleTest через FetchContent (идеально для Windows)
#
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

#
# Тесты
#
set(TEST_SOURCES
    ${TEST_DIR}/testlab_3.cpp
    ${SRC_DIR}/model.cpp
    ${SRC_DIR}/pid.cpp
)

add_executable(test_runner_ii02801 ${TEST_SOURCES})

target_link_libraries(test_runner_ii02801
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME AllTests COMMAND test_runner_ii02801)
