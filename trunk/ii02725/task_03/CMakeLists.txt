cmake_minimum_required(VERSION 3.16)
project(ii02725_task03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ОСНОВНАЯ ПРОГРАММА
add_library(ii02725_core
    src/pid.cpp
    src/plant.cpp
)

target_include_directories(ii02725_core PUBLIC src)

add_executable(ii02725_simulator
    src/main.cpp
)

target_include_directories(ii02725_simulator PUBLIC src)
target_link_libraries(ii02725_simulator PRIVATE ii02725_core)

# ТЕСТЫ 
enable_testing()

# Загрузить GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Тестовый исполняемый файл
add_executable(ii02725_tests
    test/test_pid.cpp
)

target_include_directories(ii02725_tests PRIVATE src)
target_link_libraries(ii02725_tests PRIVATE 
    ii02725_core 
    gtest 
    gtest_main
)

#COVERAGE ФЛАГИ 
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Для библиотеки core
    target_compile_options(ii02725_core PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(ii02725_core PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )

    # Для симулятора
    target_compile_options(ii02725_simulator PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(ii02725_simulator PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )

    # Для тестов
    target_compile_options(ii02725_tests PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(ii02725_tests PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )
endif()

include(GoogleTest)
gtest_discover_tests(ii02725_tests)