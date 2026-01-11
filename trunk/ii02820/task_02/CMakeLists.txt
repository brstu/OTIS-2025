# Тесты - используем имя, которое ищет система
add_executable(
  testlab3_runner_ii02820
  test_model.cpp
)

# Ссылаемся на библиотеку из src/
target_link_libraries(
  testlab3_runner_ii02820
  PRIVATE
  model_lib        # из src/
  gtest
  gtest_main
)

target_include_directories(testlab3_runner_ii02820
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

target_compile_options(testlab3_runner_ii02820 PRIVATE --coverage -g -O0)
target_link_options(testlab3_runner_ii02820 PRIVATE --coverage)

# Регистрация тестов в CTest
include(GoogleTest)
gtest_discover_tests(testlab3_runner_ii02820)