cmake_minimum_required(VERSION 3.14)
project(task_03_ii02810 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pid_sim_ii02810
    main.cpp
    pid_controller.cpp
    heater_model.cpp
)

target_include_directories(pid_sim_ii02810 PRIVATE .)

enable_testing()
find_package(GTest REQUIRED)

add_executable(pid_tests_ii02810
    ../test/pid_tests.cpp
    pid_controller.cpp
    heater_model.cpp
)

target_include_directories(pid_tests_ii02810 PRIVATE .)
target_link_libraries(pid_tests_ii02810 GTest::gtest GTest::gtest_main)
add_test(NAME pid_tests_ii02810 COMMAND pid_tests_ii02810)

find_package(Doxygen OPTIONAL_COMPONENTS dot)
if(DOXYGEN_FOUND)
    doxygen_add_docs(doxygen_html
        pid_controller.h pid_controller.cpp heater_model.h heater_model.cpp main.cpp
        ALL
        COMMENT "Генерация документации Doxygen"
    )
endif()