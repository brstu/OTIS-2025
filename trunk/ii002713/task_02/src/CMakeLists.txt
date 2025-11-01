cmake_minimum_required(VERSION 3.14)
project(ii002713_task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги покрытия кода (GCC/Clang)
set(COVERAGE_FLAGS -fprofile-arcs -ftest-coverage -O0 -g)

# Библиотека модели
add_library(ii002713_model STATIC model.cpp)
target_include_directories(ii002713_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(ii002713_model PRIVATE ${COVERAGE_FLAGS})
target_link_options(ii002713_model PRIVATE ${COVERAGE_FLAGS})

# Основной исполняемый файл
add_executable(ii002713_task_02 task_02.cpp)
target_link_libraries(ii002713_task_02 PRIVATE ii002713_model)
target_compile_options(ii002713_task_02 PRIVATE ${COVERAGE_FLAGS})
target_link_options(ii002713_task_02 PRIVATE ${COVERAGE_FLAGS})

# GoogleTest
include(FetchContent)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(runTests_ii002713 ../test/test.cpp)
target_link_libraries(runTests_ii002713 PRIVATE ii002713_model gtest gtest_main)
target_compile_options(runTests_ii002713 PRIVATE ${COVERAGE_FLAGS})
target_link_options(runTests_ii002713 PRIVATE ${COVERAGE_FLAGS})

include(GoogleTest)
gtest_discover_tests(runTests_ii002713)

# Генерация отчета покрытия gcovr
add_custom_target(coverage
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o coverage.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating code coverage report with gcovr"
)
