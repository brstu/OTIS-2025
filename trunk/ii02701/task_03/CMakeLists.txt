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

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXY_IN ${CMAKE_SOURCE_DIR}/DoxyfileNG.xml)
    set(DOXY_OUT ${CMAKE_BINARY_DIR}/DoxyfileNG.xml)

    configure_file(${DOXY_IN} ${DOXY_OUT} COPYONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXY_OUT}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating XML documentation for SonarQube"
    )
endif()