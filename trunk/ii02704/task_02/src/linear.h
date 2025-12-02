#ifndef LIN_H
#define LIN_H

#include <iostream>
#include <vector>

void input(int& k, std::vector<double>& u, std::vector<double>& y, double& a, double& b);
void linear(const int& place, const int& k, std::vector<double>& y, const std::vector<double>& u, const double& b, const double& a);

#endif
