cmake_minimum_required(VERSION 3.14)
project(PID_Lab3 LANGUAGES CXX)

# Требуем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Папка для сборки (чтобы не засорять src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Основная исполняемая программа
add_executable(pid_sim
    main.cpp
    pid_controller.cpp
    model.cpp
)

# Подключаем заголовочные файлы из текущей папки
target_include_directories(pid_sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Для красоты в Visual Studio — разбиваем по фильтрам
source_group("Source Files" FILES main.cpp pid_controller.cpp model.cpp)
source_group("Header Files" FILES pid_controller.h model.h)