@echo off
cmake -S ./src -B ./build/src
cmake --build ./build/src

cmake -S ./test -B ./build/test
cmake --build ./build/test


.\build\src\task_03_ii02707_src.exe
.\build\test\task_03_ii02707_test.exe

gcovr -r ./ --exclude ".*googletest*." 