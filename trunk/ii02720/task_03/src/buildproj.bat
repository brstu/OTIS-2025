@echo off
REM ===== Сборка проекта через CMake =====

REM Создаём папку build, если её нет
if not exist build (
    mkdir build
)

cd build

REM Генерируем проект (по умолчанию MinGW или MSVC, зависит от установленного компилятора)
cmake ..

REM Запускаем сборку
cmake --build . --config Release

cd ..
echo ===== Сборка завершена =====
