@echo off
echo Building and running PID simulation for Ruslan...

if not exist build mkdir build
cd build

echo Configuring CMake...
:: Явно указываем файл CMakeLists
cmake ../src -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

if %errorlevel% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b %errorlevel%
)

echo Building project...
cmake --build .

if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b %errorlevel%
)

echo.
echo Running simulation...
if exist pid_sim_ruslan.exe (
    .\pid_sim_ruslan.exe
) else (
    echo Executable pid_sim_ruslan.exe not found!
)

echo.
echo Running tests...
if exist runTests_ruslan_task03.exe (
    .\runTests_ruslan_task03.exe
) else (
    echo Test executable runTests_ruslan_task03.exe not found!
)

cd ..
pause