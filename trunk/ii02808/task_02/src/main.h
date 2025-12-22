#ifndef MAIN_H
#define MAIN_H

#include <vector>

extern const std::vector<double> params;
extern const double heat_input;

std::vector<double> linearSim(int n, double start_temp);
std::vector<double> nonlinearSim(int n, double start_temp);

#endif