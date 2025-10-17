# Минимальная версия CMake
cmake_minimum_required(VERSION 3.14)

# Название проекта (может быть любым)
project(lab2_src LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем статическую библиотеку lab2 из исходников
# Она содержит реализацию функций из lab2.cpp
add_library(lab2 STATIC
    lab2.cpp
)

# Указываем, где искать заголовочные файлы (чтобы можно было #include "lab2.h")
target_include_directories(lab2 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Создаём исполняемый файл (основную программу)
add_executable(lab2_app
    main.cpp
)

# Линкуем приложение с нашей библиотекой lab2
target_link_libraries(lab2_app PRIVATE lab2)

# Опционально: включаем предупреждения компилятора
if (MSVC)
    target_compile_options(lab2 PRIVATE /W4)
    target_compile_options(lab2_app PRIVATE /W4)
else()
    target_compile_options(lab2 PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(lab2_app PRIVATE -Wall -Wextra -pedantic)
endif()