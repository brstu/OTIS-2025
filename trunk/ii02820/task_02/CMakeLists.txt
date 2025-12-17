cmake_minimum_required(VERSION 3.14)
project(ii02820_task02)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(ii02820_main src/main.cpp src/model.cpp)

# Google Test (скачивается автоматически)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Тесты с Google Test
add_executable(ii02820_gtests test/test_model.cpp src/model.cpp)
target_link_libraries(ii02820_gtests PRIVATE gtest_main)
target_include_directories(ii02820_gtests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(ii02820_gtests)