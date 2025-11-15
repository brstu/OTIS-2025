#ifndef MODELSIMULATION_H
#define MODELSIMULATION_H

#include <iostream>
#include <cmath>
#include <vector>

struct LinearModelParams {
    double a;
    double b;
};

struct NonLinearModelParams {
    double yOffset;
    double uOffset;
    double a;
    double b;
    double c;
    double d;
    double u_step;
};

struct SimulationParams {
    double y;
    double u;
    int t;
};

// Function declarations
SimulationParams getDefaultSimulationParams();

std::vector<double> simulateLinearModel(const SimulationParams& simParams);
LinearModelParams getDefaultLinearParams();

std::vector<double> simulateNonLinearModel(const SimulationParams& simParams);
NonLinearModelParams getDefaultNonLinearParams();

#endif // MODELSIMULATION_H