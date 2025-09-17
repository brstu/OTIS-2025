cmake_minimum_required(VERSION 3.10...3.28)
project(lab_01_ii02818)

# Поиск всех cpp файлов
file(GLOB_RECURSE SOURCES "*.cpp")

if(SOURCES)
    message("Building with sources: ${SOURCES}")
    add_executable(lab1OTIS ${SOURCES})
else()
    # Создаем пустой target если файлов нет (для тестирования)
    add_executable(lab1OTIS "")
    message(WARNING "No source files found - creating empty target")
endif()