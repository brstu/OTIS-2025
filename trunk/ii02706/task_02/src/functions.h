#pragma once

#include <iostream>
#include <cmath>

const double first_funct_const = 0.1;
const double second_funct_const = 0.2;
const double third_funct_const = 0.3;

void liner_funcnt(double& y1);
void nonliner_funct(double& y2, double& y_previous, bool& second_iteration);