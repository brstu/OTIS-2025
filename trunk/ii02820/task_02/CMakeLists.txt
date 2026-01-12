cmake_minimum_required(VERSION 3.15)
project(task_02)

# УСТАНОВИ СТАНДАРТ C++17!
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Google Test с ПРАВИЛЬНЫМ тегом
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0  # ← ИЗМЕНИЛ release-1.14.0 на v1.14.0!
)
FetchContent_MakeAvailable(googletest)

# Библиотека
add_library(model_lib STATIC src/model.cpp)

# Основная программа
add_executable(task_02_main src/main.cpp)
target_link_libraries(task_02_main model_lib)

# Тесты
add_executable(testlab3_runner_ii02820 test/test_model.cpp)
target_link_libraries(testlab3_runner_ii02820 
    PRIVATE 
    model_lib
    gtest
    gtest_main
)

# Заголовки для тестов
target_include_directories(testlab3_runner_ii02820
    PRIVATE
    src
    ${googletest_SOURCE_DIR}/googletest/include
)