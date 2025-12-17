cmake_minimum_required(VERSION 3.16...3.30)
project(Task03 LANGUAGES C CXX)

# Включаем возможность запускать тесты
enable_testing()

# Если используется vcpkg, подключаем toolchain
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    endif()
endif()

# Добавляем подкаталоги
add_subdirectory(src)
add_subdirectory(test)