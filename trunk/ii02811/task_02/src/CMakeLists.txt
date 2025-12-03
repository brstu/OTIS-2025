cmake_minimum_required(VERSION 3.15.0)

set(VCPKG_TARGET_TRIPLET x64-windows)
include("D:\\LABS\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")

project(gtest_program)

# Основная программа
add_executable(program main.cpp model.cpp main.h)

# Тесты
enable_testing()
find_package(GTest CONFIG REQUIRED)

# Используем относительный путь
add_executable(gtest_program 
    ../test/test.cpp  # Файл на уровень выше в папке test
    model.cpp 
    main.h
)

target_link_libraries(gtest_program PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME all_test COMMAND gtest_program)