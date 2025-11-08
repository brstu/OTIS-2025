@echo off
cmake -S ./ -B ./build
cmake --build ./build

.\build\test\task_03_ii02707_test.exe