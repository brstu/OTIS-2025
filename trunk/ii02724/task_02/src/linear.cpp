#include <iostream>
#include <math.h>
#include "Linear.h"
using namespace std;

void Linear(double param_a, double param_b, int steps_count, double& current_temp, double current_heat) {
    for (int step = 1; step <= steps_count; step++)
    {
        current_temp = param_a * current_temp + param_b * current_heat;
    }
}