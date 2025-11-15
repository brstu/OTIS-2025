cmake_minimum_required(VERSION 3.14)
project(PID_Lab3_Src LANGUAGES CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Динамическая CRT (чтобы избежать LNK2038)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Исполняемый файл
add_executable(pid_sim
    main.cpp
    pid_controller.cpp
    model.cpp
)

# Подключение заголовков
target_include_directories(pid_sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Выходная папка
set_target_properties(pid_sim PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
)