# Минимальная версия CMake
cmake_minimum_required(VERSION 3.15)

# Устанавливаем политику CMP0135 для устранения предупреждения
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# Имя проекта
project(ii02811)

# Использовать стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Для Visual Studio
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
    )
endif()

# Загрузка Google Test с указанием опции времени
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE  # Добавляем эту опцию
)

FetchContent_MakeAvailable(googletest)

# Включить тестирование
enable_testing()

# 1. СОЗДАНИЕ БИБЛИОТЕКИ из файлов в текущей папке
add_library(pid_lib_ii02811
    pid.cpp
    model.cpp
)

# Заголовочные файлы находятся в текущей папке
target_include_directories(pid_lib_ii02811
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# 2. СОЗДАНИЕ ОСНОВНОЙ ПРОГРАММЫ
add_executable(pid_simulation_ii02811
    main.cpp
)

# Связываем программу с библиотекой
target_link_libraries(pid_simulation_ii02811 pid_lib_ii02811)

# 3. СОЗДАНИЕ ТЕСТОВОЙ ПРОГРАММЫ
# Файл тестов находится на уровень выше в папке test/
add_executable(pid_tests_ii02811
    ../test/test.cpp
)

# Связываем тесты с библиотекой и Google Test
target_link_libraries(pid_tests_ii02811
    pid_lib_ii02811
    gtest
    gtest_main
)

# Заголовочные файлы для тестов тоже в текущей папке
target_include_directories(pid_tests_ii02811
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Добавляем тест в систему тестирования
add_test(NAME PID_TESTS_II02811 COMMAND pid_tests_ii02811)

# 4. ГЕНЕРАЦИЯ ДОКУМЕНТАЦИИ (опционально)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    # Настройки Doxygen
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_HTML_OUTPUT html)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX NO)
    set(DOXYGEN_PROJECT_NAME "PID Controller System - Variant 11")
    set(DOXYGEN_PROJECT_NUMBER "1.0")
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXTRACT_PRIVATE YES)
    
    # Генерация документации
    doxygen_add_docs(generate_docs
        ${CMAKE_SOURCE_DIR}/Doxyfile.txt
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating Doxygen documentation"
    )
endif()