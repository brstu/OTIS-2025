cmake_minimum_required(VERSION 3.15)
project(testlab3_runner_ii02820)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ФАЙЛЫ основной программы
add_executable(${PROJECT_NAME}
    main.cpp
    lin_model.cpp
    model_validation.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE .)