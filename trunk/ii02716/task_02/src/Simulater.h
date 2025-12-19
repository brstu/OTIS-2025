#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>
#include "NonLinearSystem.h"
#include "LinearSystem.h"

struct SystemConstantsl;

void printResult(int iteration, double value);

void simulateSystem(double initialY1, int iterations);

#endif 

