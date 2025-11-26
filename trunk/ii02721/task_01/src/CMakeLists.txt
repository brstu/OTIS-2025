cmake_minimum_required(VERSION 3.10)
project(OTIS_Fedotov)

message("=== Конфигурация проекта OTIS_Fedotov ===")


file(GLOB FEDOTOV_SRC_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*/")

foreach(FEDOTOV_ITEM ${FEDOTOV_SRC_DIRS})
    if (EXISTS ${FEDOTOV_ITEM}/CMakeLists.txt)
        message(" Fedotov: найден каталог \"${FEDOTOV_ITEM}\"")
        add_subdirectory(${FEDOTOV_ITEM})
    else()
        message(" ⚠ Пропущено: ${FEDOTOV_ITEM} (нет CMakeLists.txt)")
    endif()
endforeach()

message("=== Конфигурация Fedotov завершена успешно ===")
