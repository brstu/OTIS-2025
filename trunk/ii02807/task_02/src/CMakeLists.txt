cmake_minimum_required(VERSION 3.15)
project(OtisTask02)

set(CMAKE_CXX_STANDARD 17)
 
if(MSVC)
    # Используем динамическую библиотеку времени выполнения
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    add_compile_options("$<$<CONFIG:Debug>:/MDd>")
    add_compile_options("$<$<CONFIG:Release>:/MD>")
endif()

# Основная программа
add_executable(simulation_main main.cpp model.cpp)

# Настройка для тестов
enable_testing()

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Тестовый исполняемый файл
add_executable(
  unit_tests
  ../test/test_model.cpp
  model.cpp
)

target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
  unit_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)