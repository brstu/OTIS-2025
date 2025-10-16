cmake_minimum_required(VERSION 3.5)
project(task_02_tests VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Поиск GoogleTest
find_package(GTest REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -fprofile-arcs -ftest-coverage)
elseif(MSVC)
    add_compile_options(/W4)
endif()

# Создание исполняемого файла тестов
add_executable(${PROJECT_NAME}
    test_main.cpp
    test_models.cpp
)

# Подключаем исходный код основной программы
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/models
)

# Линковка с GoogleTest и библиотеками покрытия
target_link_libraries(${PROJECT_NAME} PRIVATE 
    GTest::gtest 
    GTest::gtest_main 
    GTest::gmock
)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m gcov)
endif()

# Добавляем цель для запуска тестов
enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

message(STATUS "Test project ${PROJECT_NAME} configured successfully")