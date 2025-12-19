cmake_minimum_required(VERSION 3.15)
project(task_03_ii02825)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_FILES
    ${SRC_DIR}/lab3.cpp
    ${SRC_DIR}/pid.cpp
    ${SRC_DIR}/model.cpp
)

# Основная программа
add_executable(lab3 ${SRC_FILES})
include_directories(${SRC_DIR})

# ----------------------------
# GoogleTest через FetchContent
# ----------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0  # Note the 'v' prefix
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тестовый бинарник
add_executable(testlab3_runner
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/testlab3.cpp
    ${SRC_DIR}/pid.cpp
    ${SRC_DIR}/model.cpp
)

target_link_libraries(testlab3_runner gtest_main pthread)
include(GoogleTest)
gtest_discover_tests(testlab3_runner)
