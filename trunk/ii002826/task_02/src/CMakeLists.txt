cmake_minimum_required(VERSION 3.10)
project(task_02_ii002826 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройка компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
    add_compile_options(/W4)
endif()

find_package(Threads)

# Основное приложение
add_executable(${PROJECT_NAME}
    main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()

# Настройка Google Test
option(BUILD_TESTING "Build tests" ON)

if(BUILD_TESTING)
    # Проверяем, установлен ли Google Test
    find_package(GTest QUIET)
    
    if(NOT GTest_FOUND)
        message(STATUS "GTest not found, using FetchContent to download it")
        
        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
        )
        
        set(FETCHCONTENT_QUIET OFF)
        FetchContent_MakeAvailable(googletest)
    else()
        message(STATUS "Found GTest: ${GTEST_LIBRARY}")
    endif()

    # Тестовое приложение
    add_executable(
        model_tests
        ../test/test_models.cpp
    )

    target_compile_features(model_tests PRIVATE cxx_std_14)

    if(GTest_FOUND)
        target_link_libraries(model_tests PRIVATE GTest::gtest GTest::gtest_main)
    else()
        target_link_libraries(model_tests PRIVATE gtest gtest_main)
    endif()

    if(UNIX AND NOT APPLE)
        target_link_libraries(model_tests PRIVATE m pthread)
    endif()

    # Настройка покрытия кода
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(model_tests PRIVATE --coverage -g -O0)
        target_link_libraries(model_tests PRIVATE --coverage)
    endif()

    enable_testing()
    add_test(NAME ModelTests COMMAND model_tests)
endif()

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    COMPONENT applications
)

message(STATUS "Project ${PROJECT_NAME} configured successfully")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")