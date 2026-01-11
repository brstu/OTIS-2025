add_library(pid
    pid.cpp
)

target_include_directories(pid
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(pid_app
    main.cpp
)

target_link_libraries(pid_app
    PRIVATE pid
)