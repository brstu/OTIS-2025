cmake_minimum_required(VERSION 3.14)
project(task_03_pid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pid_sim
    src/main.cpp
    src/pid.cpp
    src/model.cpp
)

enable_testing()
find_package(GTest REQUIRED)

add_executable(pid_tests
    test/tests.cpp
    src/pid.cpp
    src/model.cpp
)

target_link_libraries(pid_tests GTest::gtest GTest::gtest_main)
add_test(NAME pid_tests COMMAND pid_tests)

find_package(Doxygen OPTIONAL_COMPONENTS dot)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX NO)
    doxygen_add_docs(doxygen
        src
        ALL
        COMMENT "Генерация HTML-документации в doc/html"
    )
endif()