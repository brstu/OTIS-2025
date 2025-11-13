cmake_minimum_required(VERSION 3.16)
project(task_03_pid LANGUAGES CXX)

option(ENABLE_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собирать бинарники прямо в src
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Основная библиотека (файлы лежат в src/)
add_library(pid_lib
    pid.cpp
    plant.cpp
    sim.cpp
)
target_include_directories(pid_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Исполняемый файл (main.cpp лежит в src/)
add_executable(pid_sim main.cpp)
target_link_libraries(pid_sim PRIVATE pid_lib)

# GoogleTest
if(ENABLE_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    # Тесты лежат в ../test/
    add_executable(pid_tests
        ../test/pid_test.cpp
        ../test/plant_test.cpp
    )
    target_include_directories(pid_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../test)
    target_link_libraries(pid_tests PRIVATE pid_lib GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(pid_tests)
endif()

# Вывод CSV: убедимся, что каталоги существуют
add_custom_command(TARGET pid_sim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/../doc/data
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/../doc/img
)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../doc/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/../doc/html)

    add_custom_target(doc_doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../doc
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

