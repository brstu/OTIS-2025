cmake_minimum_required(VERSION 3.10)
project(task_03_ii02717)  # Make project name unique

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

cmake_policy(SET CMP0079 NEW)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(runTests_ii02717 ../test/test_3.cpp  module.cpp)

#Main.cpp test
add_executable(main_ii02717 main.cpp module.cpp)
target_compile_options(main_ii02717 PRIVATE -fprofile-arcs -ftest-coverage)
target_link_options(main_ii02717 PRIVATE -fprofile-arcs -ftest-coverage)

# Установка опций покрытия для GCC/Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(runTests_ii02717 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(runTests_ii02717 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )
endif()

# Use the correct target names from FetchContent
target_link_libraries(runTests_ii02717 gtest gtest_main)

# Добавляем путь включения
target_include_directories(runTests_ii02717 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(runTests_ii02717)