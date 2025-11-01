cmake_minimum_required(VERSION 3.10)
project(ii02825_Task02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Пути к исходникам
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Основные файлы программы
set(SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp
)

# ---- Подключение GoogleTest ----
# Пути для macOS (Homebrew)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# ---- Тесты ----
# test/test.cpp находится уровнем выше
add_executable(runTests_ii02825
    ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/test.cpp
)

# Линкуем GoogleTest и pthread
target_link_libraries(runTests_ii02825 gtest gtest_main pthread)
