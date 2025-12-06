#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

std::vector<double> simulateLinearfunc(int steps, double y_init, const std::vector<double>& u);
std::vector<double> simulateNonlinearfunc(int steps, double y_init, const std::vector<double>& u);

#endif
