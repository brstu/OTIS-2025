cmake_minimum_required(VERSION 3.15)
project(lab_3_ii02820)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# ФАЙЛЫ - ДОБАВЛЕН lin_model.cpp
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/lin_model.cpp
)

# Основная программа
add_executable(task_3_ii02820 ${SRC_FILES})
include_directories(${SRC_DIR})

# ----------------------------
# ТЕСТЫ - ОСТАВЛЕНО
# ----------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.15.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тестовый бинарник
add_executable(testlab3_runner_ii02820
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/test_model.cpp
    ${SRC_DIR}/system_tests.cpp
)

# Добавить include-директории для тестов
target_include_directories(testlab3_runner_ii02820 PRIVATE
    ${SRC_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../test
)

# Правильное подключение Google Test
target_link_libraries(testlab3_runner_ii02820 
    PRIVATE 
    gtest_main 
    gtest
)

include(GoogleTest)
gtest_discover_tests(testlab3_runner_ii02820)