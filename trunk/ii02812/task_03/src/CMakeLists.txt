cmake_minimum_required(VERSION 3.15)
project(lab_3_ii02812)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/PID.cpp
    ${SRC_DIR}/lin_model.cpp
)

# Основная программа
add_executable(task_3_ii02812 ${SRC_FILES})
include_directories(${SRC_DIR})

# ----------------------------
# GoogleTest через FetchContent
# ----------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.15.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тестовый бинарник
add_executable(testlab3_runner_ii02812
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/test.cpp
    ${SRC_DIR}/PID.cpp
    ${SRC_DIR}/lin_model.cpp
)

target_link_libraries(testlab3_runner_ii02812 gtest_main pthread)
include(GoogleTest)
gtest_discover_tests(testlab3_runner_ii02812)