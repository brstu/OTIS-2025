cmake_minimum_required(VERSION 3.10)
project(task_02_ii02725)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

cmake_policy(SET CMP0079 NEW)

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
# Пути относительно src/ где лежит CMakeLists.txt
add_executable(runTests_ii02725 
    ../tests/test.cpp    # из task_02/test/
    modul.cpp          # из текущей папки (src/)
)

add_executable(main_ii02725 
    main.cpp            # из текущей папки (src/)
    modul.cpp          # из текущей папки (src/)
)

# Установка опций покрытия
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Для тестов
    target_compile_options(runTests_ii02725 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(runTests_ii02725 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )

    # Для main
    target_compile_options(main_ii02725 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(main_ii02725 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )
endif()

target_link_libraries(runTests_ii02725 gtest gtest_main)
# Добавляем include директории для тестов
target_include_directories(runTests_ii02725 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(runTests_ii02725)