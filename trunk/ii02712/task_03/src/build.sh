#!/bin/bash

echo Building Src
cmake -S ./ -B ./build
cmake --build ./build
echo Finish building Src

