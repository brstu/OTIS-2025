@echo off
cd build
runTests_ii02717.exe
gcovr -r .. --filter ".*(main|module)\.cpp$"
pause