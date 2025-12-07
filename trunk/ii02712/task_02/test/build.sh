#!/bin/bash

echo "Building Tests"
cmake -S ./ -B ./build
cmake --build ./build
echo "Finish building Tests"