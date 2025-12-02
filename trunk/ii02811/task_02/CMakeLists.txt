cmake_minimum_required(VERSION 3.15)

project(gtest_program CXX)

# Установите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(program src/main.cpp src/model.cpp)

# Тесты
enable_testing()

# Находим GTest
find_package(GTest REQUIRED)

add_executable(tests test/test.cpp src/model.cpp)
target_link_libraries(tests GTest::gtest GTest::gtest_main)
add_test(NAME UnitTests COMMAND tests)

# Настройка покрытия кода в зависимости от компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Для GCC/Clang используем стандартные флаги
    message(STATUS "Using GCC/Clang compiler - enabling gcov")
    target_compile_options(program PRIVATE -g -O0 --coverage)
    target_compile_options(tests PRIVATE -g -O0 --coverage)
    target_link_options(program PRIVATE --coverage)
    target_link_options(tests PRIVATE --coverage)
    
    # Настройка gcovr
    find_program(GCOVR gcovr)
    if(GCOVR)
        add_custom_target(coverage
            COMMAND ${GCOVR} 
                    --root ${CMAKE_SOURCE_DIR} 
                    --exclude ".*/test/.*" 
                    --exclude ".*/build/.*" 
                    --html 
                    --html-details 
                    --output ${CMAKE_BINARY_DIR}/coverage_report.html
            COMMAND ${GCOVR} 
                    --root ${CMAKE_SOURCE_DIR}
                    --exclude ".*/test/.*"
                    --exclude ".*/build/.*"
                    --output ${CMAKE_BINARY_DIR}/coverage_summary.txt
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating coverage report with gcovr..."
        )
        add_dependencies(coverage tests)
    endif()
    
elseif(MSVC)
    # Для MSVC используем встроенные инструменты
    message(STATUS "Using MSVC compiler - enabling code coverage")
    
    # Включаем отладочную информацию
    target_compile_options(program PRIVATE /Zi)
    target_compile_options(tests PRIVATE /Zi)
    
    # Для покрытия кода в MSVC можно использовать OpenCppCoverage
    find_program(OpenCppCoverage_PATH OpenCppCoverage)
    
    if(OpenCppCoverage_PATH)
        message(STATUS "Found OpenCppCoverage: ${OpenCppCoverage_PATH}")
        
        add_custom_target(coverage-msvc
            COMMAND ${OpenCppCoverage_PATH}
                    --sources ${CMAKE_SOURCE_DIR}/src
                    --export_type=html:${CMAKE_BINARY_DIR}/coverage_msvc_report
                    --modules ${CMAKE_BINARY_DIR}/Debug/*.exe
                    --cover_children
                    --quiet
            COMMAND echo "OpenCppCoverage report generated in: ${CMAKE_BINARY_DIR}/coverage_msvc_report"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating coverage report with OpenCppCoverage..."
        )
        add_dependencies(coverage-msvc tests)
        
    else()
        message(STATUS "OpenCppCoverage not found. Install it from: https://github.com/OpenCppCoverage/OpenCppCoverage")
    endif()
    
    # Альтернатива: сбор данных профилирования Visual Studio
    add_custom_target(coverage-vs
        COMMAND echo "To generate code coverage in Visual Studio:"
        COMMAND echo "1. Build in Debug configuration"
        COMMAND echo "2. Run Test Explorer"
        COMMAND echo "3. Right-click tests → Analyze Code Coverage"
        COMMAND echo "4. View results in Code Coverage Results window"
        COMMENT "Instructions for Visual Studio Code Coverage"
    )
endif()