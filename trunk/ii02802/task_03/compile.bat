@echo off
echo Building project...
if not exist build mkdir build
cd build

echo Configuring CMake...
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo CMake configuration failed!
    cd ..
    pause
    exit /b %errorlevel%
)

echo Building project...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo Build failed!
    cd ..
    pause
    exit /b %errorlevel%
)

echo.
echo Running main program...
if exist main.exe (
    echo Found main.exe
    .\main.exe
) else (
    if exist project.exe (
        echo Found project.exe
        .\project.exe
    ) else (
        if exist app.exe (
            echo Found app.exe
            .\app.exe
        ) else (
            echo Main executable not found ^(tried: main.exe, project.exe, app.exe^)
        )
    )
)

echo.
echo Running tests...
if exist task_ii2802.exe (
    echo Found task_ii2802.exe
    .\task_ii2802.exe
) else (
    if exist test\task_ii2802.exe (
        echo Found task_ii2802.exe in test subfolder
        .\test\task_ii2802.exe
    ) else (
        echo Test executable task_ii2802.exe not found!
    )
)

cd ..
echo.
echo Done.
pause
