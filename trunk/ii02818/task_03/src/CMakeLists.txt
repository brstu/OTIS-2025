cmake_minimum_required(VERSION 3.15)

project(ii02818)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
    )
endif()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(pid_lib_ii02818   # Изменено имя
    pid.cpp
    model.cpp
)

target_include_directories(pid_lib_ii02818  # Изменено имя
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)


add_executable(pid_simulation_ii02818   # Изменено имя (опционально)
    main.cpp
)

target_link_libraries(pid_simulation_ii02818 pid_lib_ii02818)  # Изменено имя


add_executable(pid_tests_ii02818   # Изменено имя
    ../test/test.cpp
)

target_link_libraries(pid_tests_ii02818  # Изменено имя
    pid_lib_ii02818  # Изменено имя
    gtest
    gtest_main
)

add_test(NAME PID_TESTS_II02818 COMMAND pid_tests_ii02818)  # Изменено имя