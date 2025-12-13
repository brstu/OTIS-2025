# Библиотека с моделями
add_library(src_lib models.cpp)

# Основное приложение
add_executable(main_app main.cpp)
target_link_libraries(main_app src_lib)
