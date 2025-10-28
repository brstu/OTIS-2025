cmake_minimum_required(VERSION 3.5)
project(task_02_ii0xxyy VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Compiler options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    add_compile_options(-Wno-error=deprecated-declarations) # For Google Test compatibility
elseif(MSVC)
    add_compile_options(/W4 /WX)
endif()

find_package(Threads REQUIRED)

# Main application
add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()

# Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(
  model_tests
  test/test_models.cpp
)

target_link_libraries(
  model_tests
  GTest::gtest_main
)

if(UNIX AND NOT APPLE)
    target_link_libraries(model_tests PRIVATE m)
endif()

# Code coverage setup for SonarQube
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        # Coverage flags
        target_compile_options(${PROJECT_NAME} PRIVATE --coverage -g -O0 -fprofile-arcs -ftest-coverage)
        target_compile_options(model_tests PRIVATE --coverage -g -O0 -fprofile-arcs -ftest-coverage)
        target_link_libraries(${PROJECT_NAME} PRIVATE --coverage)
        target_link_libraries(model_tests PRIVATE --coverage)
        
        # Test discovery for SonarQube
        enable_testing()
        add_test(NAME model_tests COMMAND model_tests)
    endif()
endif()

# Installation
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    COMPONENT applications
)

# SonarQube helper targets
add_custom_target(sonar-scanner
    COMMAND echo "Run: sonar-scanner -Dproject.settings=sonar-project.properties"
    COMMENT "SonarQube analysis target"
)

add_custom_target(coverage-report
    COMMAND ./model_tests
    COMMAND gcovr -r . --xml-pretty > coverage_report.xml
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating coverage report for SonarQube"
    DEPENDS model_tests
)

# Static analysis targets
add_custom_target(static-analysis
    COMMAND echo "Running static analysis tools..."
    COMMENT "Static analysis target"
)

message(STATUS "Project ${PROJECT_NAME} configured successfully")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build directory: ${CMAKE_BINARY_DIR}")