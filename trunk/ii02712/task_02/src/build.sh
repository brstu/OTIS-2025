#!/bin/bash

echo "Building Application"
cmake -S ./ -B ./build
cmake --build ./build
echo "Finish building Application"