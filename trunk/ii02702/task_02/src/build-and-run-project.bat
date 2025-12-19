@echo off
cmake -S ./ -B ./build -G "MinGW Makefiles"
cmake --build ./build

.\build\task_02_ii02702_src.exe