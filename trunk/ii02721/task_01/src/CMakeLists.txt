cmake_minimum_required(VERSION 3.0.0)
project(OTIS_Fedotov)

message("=== Конфигурация проекта OTIS_Fedotov ===")

file(GLOB FEDOTOV_SRC_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*/")

foreach(FEDOTOV_ITEM ${FEDOTOV_SRC_DIRS})
    message(" Fedotov: найден каталог \"${FEDOTOV_ITEM}\"")
    add_subdirectory(${FEDOTOV_ITEM})
endforeach()

message("=== Конфигурация Fedotov завершена успешно ===")
