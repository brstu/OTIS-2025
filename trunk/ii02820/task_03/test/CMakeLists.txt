cmake_minimum_required(VERSION 3.5)
project(task_03_ii02820_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги coverage только для GCC/Clang (не для MSVC)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ДОБАВЬ lin_model.cpp сюда тоже!
add_executable(
    ${CMAKE_PROJECT_NAME}
    test_model.cpp
    ../src/lin_model.cpp  # ДОБАВЛЕНО!
)

# ДОБАВИТЬ ЭТУ СЕКЦИЮ - include директории
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src  
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    gtest
    gmock
)

# Добавляем флаги coverage только для GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE --coverage -g -O0)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE --coverage)
endif()

#include(GoogleTest)
#gtest_discover_tests(${CMAKE_PROJECT_NAME})