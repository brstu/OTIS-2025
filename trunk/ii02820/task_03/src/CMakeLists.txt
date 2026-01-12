cmake_minimum_required(VERSION 3.15)
project(testlab3_runner_ii02820)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# ФАЙЛЫ основной программы
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/lin_model.cpp
    ${SRC_DIR}/model_validation.cpp
)

# Основная программа
add_executable(${PROJECT_NAME} ${SRC_FILES})
include_directories(${SRC_DIR})

# ----------------------------
# ТЕСТЫ
# ----------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.15.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тестовый бинарник - ДРУГОЕ ИМЯ!
add_executable(${PROJECT_NAME}_tests
    ${SRC_DIR}/../test/test_model.cpp
    ${SRC_DIR}/lin_model.cpp
    ${SRC_DIR}/model_validation.cpp
)

# Добавить include-директории для тестов
target_include_directories(${PROJECT_NAME}_tests PRIVATE
    ${SRC_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../test
)

# Правильное подключение Google Test
target_link_libraries(${PROJECT_NAME}_tests 
    PRIVATE 
    gtest_main 
    gtest
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)