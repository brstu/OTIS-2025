cmake_minimum_required(VERSION 3.15)

# Загружаем Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.14.0
)
FetchContent_MakeAvailable(googletest)

# Создаем тесты
add_executable(testlab3_runner_ii02820 test_model.cpp)

# Линкуем с библиотекой И Google Test
target_link_libraries(testlab3_runner_ii02820
    PRIVATE
    model_lib          # из src/
    gtest              # Google Test
    gtest_main         # main для тестов
)

# Включаем заголовки
target_include_directories(testlab3_runner_ii02820
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${googletest_SOURCE_DIR}/googletest/include
)

# Регистрируем тесты для CTest
include(GoogleTest)
gtest_discover_tests(testlab3_runner_ii02820)