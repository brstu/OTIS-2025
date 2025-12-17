# Конфигурация проекта для системы моделирования
cmake_minimum_required(VERSION 3.25)

# Настройка проекта
project(SystemSimulatorProject)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Включение системы тестирования
enable_testing()

# Создание исполняемого файла для тестов
add_executable(
    system_simulator_tests
    functions.cpp
    ../test/test.cpp  # Обрати внимание на путь
)

# Настройка директорий с заголовочными файлами
target_include_directories(system_simulator_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../test
)

# Подключение библиотек тестирования (gtest_main уже должен быть доступен)
# Убедись, что эти цели существуют (их создаст корневой CMakeLists)
target_link_libraries(
    system_simulator_tests
    GTest::gtest_main
)

# Автоматическая регистрация тестов
include(GoogleTest)
gtest_discover_tests(system_simulator_tests)
