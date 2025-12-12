@echo off
cmake -S ./ -B ./build
cmake --build ./build

.\build\Debug\task_02_ii02702_src.exe