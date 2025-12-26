@echo off
REM Windows build script for PID controller - UNIQUE NAMES

set PROJECT_ROOT=%~dp0
set BUILD_DIR=%PROJECT_ROOT%build

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

echo.
echo   Building Debug configuration (CMake)
echo.

cd /d "%BUILD_DIR%"
cmake -G "Visual Studio 16 2019" -A x64 "%PROJECT_ROOT%src"
if errorlevel 1 (
    echo CMake failed!
    pause
    exit /b 1
)

cmake --build . --config Debug
if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo          Running Google Tests
echo.

if exist "%BUILD_DIR%\Debug\runTests_ii002722.exe" (
    "%BUILD_DIR%\Debug\runTests_ii002722.exe"
) else (
    echo "Test executable not found!"
    dir "%BUILD_DIR%\Debug\*"
)

echo.
echo        Running main program
echo.

if exist "%BUILD_DIR%\Debug\pid_sim_ii002722.exe" (
    "%BUILD_DIR%\Debug\pid_sim_ii002722.exe"
) else (
    echo "Main executable not found!"
    dir "%BUILD_DIR%\Debug\*"
)

echo.
echo       Opening GitHub Pages documentation
echo.

start "" "https://topg1616.github.io/OTIS-2025/"

echo.
echo       All done: Build, Tests, Docs
pause