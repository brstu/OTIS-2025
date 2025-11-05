#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

std::vector<double> simulateLinear(int steps, double y_init, const std::vector<double>& u);
std::vector<double> simulateNonlinear(int steps, double y_init, const std::vector<double>& u);

#endif
