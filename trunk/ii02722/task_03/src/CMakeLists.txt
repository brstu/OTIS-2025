cmake_minimum_required(VERSION 3.14)
project(ii02822_task_03 LANGUAGES CXX)

# Политика для FetchContent (убирает предупреждение CMP0135)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Настройки компиляции
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Пути
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../test)

# Библиотеки
add_library(model_ii02822 STATIC ${SRC_DIR}/model.cpp)
target_include_directories(model_ii02822 PUBLIC ${SRC_DIR})

add_library(pid_lib_ii02822 STATIC ${SRC_DIR}/pid.cpp)
target_include_directories(pid_lib_ii02822 PUBLIC ${SRC_DIR})

# Основной exe
add_executable(pid_sim_ii02822 ${SRC_DIR}/main.cpp)
target_link_libraries(pid_sim_ii02822 PRIVATE pid_lib_ii02822 model_ii02822)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# Тесты
if(EXISTS ${TEST_DIR})
    add_executable(runTests_ii02822 ${TEST_DIR}/test_pid.cpp)
    target_link_libraries(runTests_ii02822 PRIVATE gtest_main pid_lib_ii02822 model_ii02822)
    target_include_directories(runTests_ii02822 PRIVATE ${SRC_DIR})
    gtest_discover_tests(runTests_ii02822)
else()
    message(WARNING "Test directory not found: ${TEST_DIR}")
endif()
