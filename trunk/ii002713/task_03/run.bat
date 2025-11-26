@echo off
REM Windows-only build script (run.bat)
REM Requires Windows, Visual Studio and CMake installed.
REM Documentation is now hosted on GitHub Pages:
REM https://topg1616.github.io/OTIS-2025/

REM Set build directory inside src
set BUILD_DIR=%~dp0src\build

REM Create build folder if not exists
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

echo.
echo   Building Debug configuration (CMake)
echo.

cmake -S "%~dp0src" -B "%BUILD_DIR%" -A x64 -DCMAKE_BUILD_TYPE=Debug
cmake --build "%BUILD_DIR%" --config Debug

echo.
echo          Running Google Tests
echo.

"%BUILD_DIR%\Debug\runTests_ii002713_task03.exe"

echo.
echo        Running main program (pid_sim)
echo.

"%BUILD_DIR%\Debug\pid_sim.exe"

echo.
echo    Opening GitHub Pages documentation
echo.

start "" "https://topg1616.github.io/OTIS-2025/"

echo.
echo       All done: Build, Tests, Docs
pause
