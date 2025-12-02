#ifndef LIN_H
#define LIN_H
#include <iostream>
#include <vector>

using namespace std;

void input(int& k, vector<double> &u, vector<double> &y, double& a, double& b);
void linear(const int& place, const int& k, vector<double>& y, const vector<double>& u, const double& b, const double& a);

#endif 
