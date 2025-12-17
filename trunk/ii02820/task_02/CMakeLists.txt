cmake_minimum_required(VERSION 3.14)
project(ModelLab CXX)

# Используем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(model_app src/main.cpp src/model.cpp)

# --- GOOGLE TEST ---
# Локальная копия GTest
add_subdirectory(libs/googletest)

# Исполняемый файл тестов
add_executable(model_tests test/test_model.cpp src/model.cpp)

# Подключаем GTest
target_link_libraries(model_tests PRIVATE gtest gtest_main)

# Заголовочные файлы
target_include_directories(model_tests 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)

# Включаем поддержку Google Test
include(GoogleTest)
gtest_discover_tests(model_tests)
