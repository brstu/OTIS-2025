cmake_minimum_required(VERSION 3.10)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включить поддержку покрытия для MSVC
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DEBUG")
endif()

# --- Настройка Google Test ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# --- Сборка тестового исполняемого файла ---
add_executable(runTests ../test/test.cpp module.cpp)

# Установка опций покрытия для разных компиляторов
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Для GCC/Clang
    target_compile_options(runTests PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(runTests PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )
elseif(MSVC)
    # Для MSVC (Visual Studio)
    target_compile_options(runTests PRIVATE 
        "/DEBUG"
    )
endif()

# Линкуем тесты с Google Test
target_link_libraries(runTests GTest::gtest GTest::gtest_main)

# Добавляем путь включения
target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(runTests)