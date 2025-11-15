cmake_minimum_required(VERSION 3.14)
project(PID_Lab3_Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Динамическая CRT
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Исполняемый файл
add_executable(pid_tests
    pid_test.cpp
    ../src/pid_controller.cpp
    ../src/model.cpp
)

target_include_directories(pid_tests PRIVATE ../src)
target_link_libraries(pid_tests gtest_main gtest)

# Тесты
add_test(NAME StepResponse     COMMAND pid_tests --gtest_filter=PIDController.StepResponse)
add_test(NAME SineTracking     COMMAND pid_tests --gtest_filter=PIDController.SineTracking)
add_test(NAME ResetClearsState COMMAND pid_tests --gtest_filter=PIDController.ResetClearsState)

include(GoogleTest)
gtest_discover_tests(pid_tests)