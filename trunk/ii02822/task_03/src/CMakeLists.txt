cmake_minimum_required(VERSION 3.15)
project(task_03_ii02822)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_FILES
    ${SRC_DIR}/main.cpp          
    ${SRC_DIR}/pid_controller.cpp 
    ${SRC_DIR}/model.cpp
)

# Основная программа
add_executable(lab3_ii02822 ${SRC_FILES})  
include_directories(${SRC_DIR})

# ----------------------------
# GoogleTest через FetchContent
# ----------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тестовый бинарник
add_executable(pid_tests_ii02822  
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/pid_controller_test.cpp
    ${SRC_DIR}/pid_controller.cpp  
    ${SRC_DIR}/model.cpp
)

target_link_libraries(pid_tests_ii02822 gtest_main pthread)
include(GoogleTest)
gtest_discover_tests(pid_tests_ii02822)