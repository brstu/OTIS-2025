# Создать исполняемый файл для тестов
add_executable(task_02_test test_model.cpp)

# Связать с библиотекой и GoogleTest
target_link_libraries(task_02_test
    PRIVATE
        model_lib
        gtest
        gtest_main
)

# Добавить директории с заголовками
target_include_directories(task_02_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

# Добавить тест в CTest
include(GoogleTest)
gtest_discover_tests(task_02_test)