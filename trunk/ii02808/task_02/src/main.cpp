#include "main.h"
#include <cmath>

const std::vector<double> params{ 0.8, 0.6, 0.4, 2.2 };
const double heat_input = 0.8;

std::vector<double> linearSim(int n, double start_temp) {
    if (n <= 0) {
        return {};
    }
    
    std::vector<double> data(n);
    data[0] = start_temp;

    for (int i = 1; i < n; i++) {
        data[i] = params[0] * data[i - 1] + params[1] * heat_input;
    }
    return data;
}

std::vector<double> nonlinearSim(int n, double start_temp) {
    if (n <= 0) {
        return {};
    }
    
    std::vector<double> data(n);
    data[0] = start_temp;

    if (n > 1) {
        data[1] = params[0] * data[0] + params[2] * heat_input + params[3] * sin(heat_input);
    }

    for (int i = 2; i < n; i++) {
        data[i] = params[0] * data[i - 1] - params[1] * data[i - 2] * data[i - 2]
            + params[2] * heat_input + params[3] * sin(heat_input);
    }
    return data;
}