cmake_minimum_required(VERSION 3.15)
project(ii002820)

# Укажите путь к vcpkg toolchain ДО project()
set(VCPKG_ROOT "C:/Users/anton/OTIS-2025/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# Установите путь к GTest конфигурации
set(GTest_DIR "${VCPKG_ROOT}/installed/x64-windows/share/gtest")
find_package(GTest REQUIRED CONFIG)

# Ищем GoogleTest через vcpkg (только CONFIG mode)
find_package(GTest REQUIRED CONFIG NO_MODULE)
message(STATUS "GoogleTest найден через vcpkg: ${GTest_VERSION}")

# Основная программа
add_executable(ii002820_model src/main.cpp src/model.cpp)
target_include_directories(ii002820_model PRIVATE src)

# Тесты
add_executable(model_tests test/model_tests.cpp src/model.cpp)
target_include_directories(model_tests PRIVATE src)

# Связываем с GoogleTest
target_link_libraries(model_tests PRIVATE GTest::gtest GTest::gtest_main)

# Включаем тестирование
enable_testing()
add_test(NAME ModelTests COMMAND model_tests)

message(STATUS "=== Проект настроен ===")