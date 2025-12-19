# Создать библиотеку из вашего кода
add_library(model_lib STATIC model.cpp model.h)

# Создать исполняемый файл для основной программы
add_executable(task_02_program main.cpp)
target_link_libraries(task_02_program model_lib)