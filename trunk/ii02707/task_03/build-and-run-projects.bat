@echo off
echo Start build src
cmake -S ./src -B ./build/src
cmake --build ./build/src
echo Finished build src

echo Start build test
cmake -S ./test -B ./build/test
cmake --build ./build/test
echo Finished build test

.\build\src\task_03_ii02707_src.exe
.\build\test\task_03_ii02707_test.exe

gcovr -r ./ --exclude ".*googletest*." 

echo Finished Build
pause