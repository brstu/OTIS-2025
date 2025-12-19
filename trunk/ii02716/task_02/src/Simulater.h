#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>
#include "NonLinearSystem.h"
#include "LinearSystem.h"

struct SystemConstantsl;

void printResult(int iteration, float value);

void simulateSystem(float initialY1, int iterations);

#endif 

