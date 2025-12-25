@echo off
chcp 65001 > nul
echo ===== Сборка проекта PID Controller =====
echo.

cd /d "%~dp0"

echo 1. Подготовка файлов...
echo.

REM Удаляем старый тестовый файл если есть
if exist "pid_controller_test.cpp" del pid_controller_test.cpp

REM Копируем тестовый файл из папки test
if exist "..\test\pid_controller_test.cpp" (
    copy "..\test\pid_controller_test.cpp" . > nul
    echo [✓] Тестовый файл скопирован: pid_controller_test.cpp
) else (
    echo [✗] Ошибка: Файл ..\test\pid_controller_test.cpp не найден!
    pause
    exit /b 1
)

REM Проверяем, что файл действительно скопировался
if not exist "pid_controller_test.cpp" (
    echo [✗] Ошибка: Не удалось скопировать тестовый файл!
    pause
    exit /b 1
)

echo.
echo 2. Проверка файлов в текущей папке:
dir *.cpp *.h
echo.

echo 3. Очистка предыдущей сборки...
if exist "build" (
    echo   Удаление папки build...
    rmdir /s /q build
)

echo 4. Создание папки сборки...
mkdir build
cd build

echo 5. Конфигурация CMake...
cmake .. -G "Visual Studio 17 2022" -A x64

if %errorlevel% neq 0 (
    echo [ОШИБКА] Конфигурация CMake не удалась!
    cd ..
    pause
    exit /b 1
)

echo 6. Сборка проекта...
cmake --build . --config Release

if %errorlevel% neq 0 (
    echo [ОШИБКА] Сборка не удалась!
    cd ..
    pause
    exit /b 1
)

cd ..

echo.
echo ===== Сборка завершена =====
echo.

echo Проверка результатов:
echo ---------------------

set EXE_FOUND=0
set TEST_FOUND=0

if exist "build\Release\lab3.exe" (
    echo [✓] Основная программа: build\Release\lab3.exe
    set EXE_PATH=build\Release\lab3.exe
    set EXE_FOUND=1
) else if exist "build\lab3.exe" (
    echo [✓] Основная программа: build\lab3.exe
    set EXE_PATH=build\lab3.exe
    set EXE_FOUND=1
) else (
    echo [✗] Основная программа не найдена
)

if exist "build\Release\pid_tests.exe" (
    echo [✓] Тесты: build\Release\pid_tests.exe
    set TEST_PATH=build\Release\pid_tests.exe
    set TEST_FOUND=1
) else if exist "build\pid_tests.exe" (
    echo [✓] Тесты: build\pid_tests.exe
    set TEST_PATH=build\pid_tests.exe
    set TEST_FOUND=1
) else (
    echo [✗] Тесты не найдены
    echo Показываю содержимое папки build\Release:
    if exist build\Release dir build\Release\*.exe
)

echo.

if %EXE_FOUND% equ 0 (
    echo [ОШИБКА] Основная программа не собрана!
    pause
    exit /b 1
)

:menu
echo Интерактивное меню:
echo -------------------
echo 1. Запустить основную программу
if %TEST_FOUND% equ 1 echo 2. Запустить тесты
echo 3. Выход
set /p choice="Выберите действие: "

if "%choice%"=="1" (
    echo.
    echo === Запуск основной программы ===
    echo.
    %EXE_PATH%
) else if "%choice%"=="2" (
    if %TEST_FOUND% equ 1 (
        echo.
        echo === Запуск тестов ===
        echo.
        %TEST_PATH%
    ) else (
        echo Тесты не найдены!
    )
) else (
    echo Выход...
    goto :eof
)

echo.
pause
goto menu