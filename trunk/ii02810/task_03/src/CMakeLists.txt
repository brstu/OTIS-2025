cmake_minimum_required(VERSION 3.14)
project(task_03_ii02810 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(pid_sim_ii02810
    main.cpp
  pid.cpp
  model.cpp
)

enable_testing()
add_executable(pid_tests_ii02810
  ../test/tests.cpp
  pid.cpp
  model.cpp
)
target_link_libraries(pid_tests_ii02810 GTest::gtest_main)
add_test(NAME pid_tests_ii02810 COMMAND pid_tests_ii02810)

find_package(Doxygen OPTIONAL_COMPONENTS dot)
if(DOXYGEN_FOUND)
  doxygen_add_docs(doc_html ../doc ALL COMMENT "Doxygen")
endif()