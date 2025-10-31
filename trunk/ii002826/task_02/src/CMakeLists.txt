cmake_minimum_required(VERSION 3.10)
project(task_02_ii002826 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем директорию с заголовками
include_directories(../include)

# Основное приложение
add_executable(${PROJECT_NAME} main.cpp)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} m)
endif()

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Тестовое приложение
add_executable(model_tests ../test/test_models.cpp)
target_link_libraries(model_tests gtest gtest_main)

if(UNIX AND NOT APPLE)
    target_link_libraries(model_tests m pthread)
endif()

enable_testing()
add_test(NAME ModelTests COMMAND model_tests)