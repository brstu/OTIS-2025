#pragma once

#include <iostream>
#include <cmath>
#include <vector>

const double first_funct_const = 0.1;
const double second_funct_const = 0.2;
const double third_funct_const = 0.3;

const double K  = 0.01;
const double T0 = 1;
const double Td = 10;
const double T = 0.5;

const double q0 = K * (1.0 + Td/T0);
const double q1 = -K * (1.0 + 2.0 * Td/T0 - T0/T);
const double q2 = K * Td/T0;


void liner_funcnt(double& y1);
double nonliner_funct (double& y2, double& y_previous, bool& second_iteration);
std::vector<double> simulatePIDRegulatorByNonLinearModel(double w, int steps);