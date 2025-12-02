cmake_minimum_required(VERSION 3.15.0)

set(VCPKG_TARGET_TRIPLET x64-windows)
include("D:\\LABS\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")

project(gtest_program)

add_executable(program src/main.cpp src/model.cpp src/main.h)
include_directories(include)

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(gtest_program test/test.cpp src/model.cpp src/main.h)
target_link_libraries(gtest_program PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME all_test COMMAND gtest_program)

# ============================================================================
# ДОБАВЛЯЕМ ПОДДЕРЖКУ GCOVR
# ============================================================================

# Опция для включения/выключения gcovr
option(ENABLE_GCOVR "Enable gcovr code coverage" ON)

# Флаги для покрытия кода (только для GCC/Clang компиляторов)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "GCC/Clang compiler detected - enabling coverage flags")
    # Добавляем флаги покрытия к тестовой программе
    target_compile_options(gtest_program PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_libraries(gtest_program PRIVATE gcov)
    
    # Также добавляем к основной программе для полноты
    target_compile_options(program PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_libraries(program PRIVATE gcov)
endif()

# Проверяем доступность gcovr через Python
find_package(Python3 COMPONENTS Interpreter)

if(Python3_Interpreter_FOUND AND ENABLE_GCOVR)
    message(STATUS "Python3 found: ${Python3_EXECUTABLE}")
    
    # Проверяем установлен ли gcovr
    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import gcovr; print('gcovr is available')"
        RESULT_VARIABLE GCOVR_AVAILABLE
        OUTPUT_VARIABLE GCOVR_OUTPUT
        ERROR_VARIABLE GCOVR_ERROR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    if(GCOVR_AVAILABLE EQUAL 0)
        message(STATUS "gcovr is available")
        
        # Основная цель для coverage с gcovr
        add_custom_target(coverage
            COMMAND ${CMAKE_COMMAND} -E echo "=========================================="
            COMMAND ${CMAKE_COMMAND} -E echo "Running tests for code coverage analysis"
            COMMAND ${CMAKE_COMMAND} -E echo "=========================================="
            COMMAND ${CMAKE_COMMAND} -E echo ""
            
            # Запускаем тесты
            COMMAND $<TARGET_FILE:gtest_program> --gtest_color=yes --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results.xml
            
            COMMAND ${CMAKE_COMMAND} -E echo ""
            COMMAND ${CMAKE_COMMAND} -E echo "=========================================="
            COMMAND ${CMAKE_COMMAND} -E echo "Generating coverage report with gcovr"
            COMMAND ${CMAKE_COMMAND} -E echo "=========================================="
            COMMAND ${CMAKE_COMMAND} -E echo ""
            
            # Генерируем HTML отчет
            COMMAND ${Python3_EXECUTABLE} -m gcovr 
                    --root ${CMAKE_SOURCE_DIR}
                    --exclude=".*/test/.*"
                    --exclude=".*/build/.*"
                    --exclude=".*/vcpkg/.*"
                    --html
                    --html-details
                    --html-title "Code Coverage Report"
                    --output ${CMAKE_BINARY_DIR}/coverage_report.html
            
            # Генерируем текстовый отчет
            COMMAND ${Python3_EXECUTABLE} -m gcovr 
                    --root ${CMAKE_SOURCE_DIR}
                    --exclude=".*/test/.*"
                    --exclude=".*/build/.*"
                    --exclude=".*/vcpkg/.*"
                    --print-summary
                    --output ${CMAKE_BINARY_DIR}/coverage_summary.txt
            
            # Генерируем отчет в формате XML (для CI)
            COMMAND ${Python3_EXECUTABLE} -m gcovr 
                    --root ${CMAKE_SOURCE_DIR}
                    --exclude=".*/test/.*"
                    --exclude=".*/build/.*"
                    --exclude=".*/vcpkg/.*"
                    --xml
                    --output ${CMAKE_BINARY_DIR}/coverage.xml
            
            COMMAND ${CMAKE_COMMAND} -E echo ""
            COMMAND ${CMAKE_COMMAND} -E echo "=========================================="
            COMMAND ${CMAKE_COMMAND} -E echo "Coverage reports generated:"
            COMMAND ${CMAKE_COMMAND} -E echo "  HTML:      ${CMAKE_BINARY_DIR}/coverage_report.html"
            COMMAND ${CMAKE_COMMAND} -E echo "  Summary:   ${CMAKE_BINARY_DIR}/coverage_summary.txt"
            COMMAND ${CMAKE_COMMAND} -E echo "  XML:       ${CMAKE_BINARY_DIR}/coverage.xml"
            COMMAND ${CMAKE_COMMAND} -E echo "  Test results: ${CMAKE_BINARY_DIR}/test_results.xml"
            COMMAND ${CMAKE_COMMAND} -E echo "=========================================="
            
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running tests and generating gcovr coverage reports"
        )
        
        # Отдельная цель только для HTML отчета (если тесты уже запущены)
        add_custom_target(coverage-html
            COMMAND ${CMAKE_COMMAND} -E echo "Generating HTML coverage report..."
            COMMAND ${Python3_EXECUTABLE} -m gcovr 
                    --root ${CMAKE_SOURCE_DIR}
                    --exclude=".*/test/.*"
                    --exclude=".*/build/.*"
                    --exclude=".*/vcpkg/.*"
                    --html
                    --html-details
                    --html-title "Code Coverage Report"
                    --output ${CMAKE_BINARY_DIR}/coverage_report.html
            COMMAND ${CMAKE_COMMAND} -E echo "HTML report generated: ${CMAKE_BINARY_DIR}/coverage_report.html"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating HTML coverage report with gcovr"
        )
        
        # Цель для быстрого просмотра coverage в консоли
        add_custom_target(coverage-console
            COMMAND ${CMAKE_COMMAND} -E echo "Code coverage summary:"
            COMMAND ${Python3_EXECUTABLE} -m gcovr 
                    --root ${CMAKE_SOURCE_DIR}
                    --exclude=".*/test/.*"
                    --exclude=".*/build/.*"
                    --exclude=".*/vcpkg/.*"
                    --print-summary
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Showing coverage summary in console"
        )
        
    else()
        # gcovr не найден
        message(STATUS "gcovr not found. Install with: pip install gcovr")
        
        add_custom_target(coverage
            COMMAND ${CMAKE_COMMAND} -E echo "ERROR: gcovr not found!"
            COMMAND ${CMAKE_COMMAND} -E echo ""
            COMMAND ${CMAKE_COMMAND} -E echo "To enable code coverage reporting:"
            COMMAND ${CMAKE_COMMAND} -E echo "1. Install gcovr: pip install gcovr"
            COMMAND ${CMAKE_COMMAND} -E echo "2. Re-run cmake"
            COMMAND ${CMAKE_COMMAND} -E echo ""
            COMMAND ${CMAKE_COMMAND} -E echo "For now, just running tests..."
            COMMAND $<TARGET_FILE:gtest_program> --gtest_color=yes
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "gcovr not found - showing installation instructions"
        )
    endif()
    
elseif(ENABLE_GCOVR)
    # Python не найден, но gcovr включен
    message(STATUS "Python3 not found - gcovr disabled")
    
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E echo "ERROR: Python3 not found!"
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "gcovr requires Python3."
        COMMAND ${CMAKE_COMMAND} -E echo "Install Python3 or disable gcovr:"
        COMMAND ${CMAKE_COMMAND} -E echo "  cmake -DENABLE_GCOVR=OFF .."
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "Running tests without coverage..."
        COMMAND $<TARGET_FILE:gtest_program> --gtest_color=yes
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Python3 not found - cannot run gcovr"
    )
    
else()
    # gcovr отключен через опцию
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E echo "Code coverage (gcovr) is disabled"
        COMMAND ${CMAKE_COMMAND} -E echo "To enable: cmake -DENABLE_GCOVR=ON .."
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "Running tests..."
        COMMAND $<TARGET_FILE:gtest_program> --gtest_color=yes
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running tests (coverage disabled)"
    )
endif()

# Цель для очистки coverage данных
add_custom_target(coverage-clean
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning coverage data..."
    COMMAND ${CMAKE_COMMAND} -E remove -f *.gcda *.gcno
    COMMAND ${CMAKE_COMMAND} -E remove -f coverage_report.html coverage_summary.txt coverage.xml
    COMMAND ${CMAKE_COMMAND} -E remove -f test_results.xml
    COMMAND ${CMAKE_COMMAND} -E echo "Coverage data cleaned"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning coverage data files"
)

# Цель для быстрого запуска тестов (без coverage)
add_custom_target(run-tests
    COMMAND $<TARGET_FILE:gtest_program> --gtest_color=yes --gtest_brief=1
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests quickly"
)

# Информационное сообщение при конфигурации
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message(STATUS "MSVC compiler detected: gcovr requires GCC/Clang for code coverage")
    message(STATUS "For MSVC, consider using OpenCppCoverage instead")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Compiler supports gcov: ${CMAKE_CXX_COMPILER_ID}")
endif()

message(STATUS "Available targets:")
message(STATUS "  cmake --build . --target run-tests    # Run tests quickly")
message(STATUS "  cmake --build . --target coverage     # Run tests with coverage report")
message(STATUS "  cmake --build . --target coverage-clean # Clean coverage data")