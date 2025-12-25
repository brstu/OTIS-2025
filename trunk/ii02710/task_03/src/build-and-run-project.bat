@echo off
cmake -S ./ -B ./build -G "MinGW Makefiles"
cmake --build ./build

.\build\task_03_ii02710_src.exe
python plot_temperature.py