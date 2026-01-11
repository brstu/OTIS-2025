@echo off
cmake -S ./ -B ./build
cmake --build ./build

.\build\Debug\task_03_ii02708_test.exe