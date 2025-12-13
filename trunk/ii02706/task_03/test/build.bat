@echo off
cmake -S ./ -B ./build -G "MinGW Makefiles"
cmake --build ./build

.\build\task_03_ii02706_test.exe