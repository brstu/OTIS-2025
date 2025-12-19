@echo off
REM Windows build script
REM Замените ii002722 на ваш правильный номер

set BUILD_DIR=%~dp0..\build

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

echo.
echo   Building Debug configuration (CMake)
echo.

cd /d "%BUILD_DIR%"
cmake -G "Visual Studio 16 2019" -A x64 "%~dp0src"
cmake --build . --config Debug

echo.
echo          Running Google Tests
echo.

if exist ".\Debug\runTests.exe" (
    .\Debug\runTests.exe
) else (
    echo "Test executable not found!"
)

echo.
echo        Running main program (pid_sim)
echo.

if exist ".\Debug\pid_sim.exe" (
    .\Debug\pid_sim.exe
) else (
    echo "Main executable not found!"
)

echo.
echo       All done
pause