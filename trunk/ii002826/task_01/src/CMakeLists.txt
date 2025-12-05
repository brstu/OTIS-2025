cmake_minimum_required(VERSION 3.5)
project(task_01_ii002826 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
    add_compile_options(/W4)
endif()

find_package(Threads)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    COMPONENT applications
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
    elseif(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
    endif()
endif()

message(STATUS "Project ${PROJECT_NAME} configured successfully")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")