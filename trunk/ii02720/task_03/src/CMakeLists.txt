cmake_minimum_required(VERSION 3.15)
project(task_03_ii02720)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_FILES
    ${SRC_DIR}/lab3main.cpp
    ${SRC_DIR}/pid.cpp
    ${SRC_DIR}/model.cpp
)

# Основная программа
add_executable(lab3_ii02720 ${SRC_FILES})
include_directories(${SRC_DIR})

# ----------------------------
# GoogleTest через FetchContent
# ----------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тестовый бинарник
add_executable(testlab3_ii02720_runner
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/testlab_3.cpp
    ${SRC_DIR}/pid.cpp
    ${SRC_DIR}/model.cpp
)

target_link_libraries(testlab3_ii02720_runner gtest_main)
include(GoogleTest)
gtest_discover_tests(testlab3_ii02720_runner)