cmake_minimum_required(VERSION 3.10)
project(task_02_ii002826 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройка компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
    add_compile_options(/W4)
endif()

find_package(Threads)

# Основное приложение
add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()

# Настройка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fd028e5530d6d9d6b7d8be.zip
)

FetchContent_MakeAvailable(googletest)

# Тестовое приложение
add_executable(
  model_tests
  test/test_models.cpp
  src/main.cpp  # Добавляем исходный код для тестирования
)

target_link_libraries(
  model_tests
  GTest::gtest_main
)

if(UNIX AND NOT APPLE)
    target_link_libraries(model_tests PRIVATE m)
endif()

# Настройка покрытия кода
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE --coverage -g -O0)
    target_compile_options(model_tests PRIVATE --coverage -g -O0)
    target_link_libraries(${PROJECT_NAME} PRIVATE --coverage)
    target_link_libraries(model_tests PRIVATE --coverage)
endif()

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    COMPONENT applications
)

enable_testing()
add_test(NAME ModelTests COMMAND model_tests)

message(STATUS "Project ${PROJECT_NAME} configured successfully")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")