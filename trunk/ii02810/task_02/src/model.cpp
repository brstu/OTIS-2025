#include "model.h"
#include <cmath>
#include <iostream>

std::vector<float> Linemodel(float y, float u, int steps, float a, float b) {
    std::vector<float> result;
    for (int i = 0; i < steps; ++i) {
        y = a * y + b * u;
        result.push_back(y);
    }
    return result;
}

std::vector<float> UnLinemodel(const Params& p, float y, float y0) {
    std::vector<float> result;
    if (p.steps <= 0 || p.steps > 10000) {
        std::cerr << "Error: invalid value p.steps = " << p.steps << std::endl;
        return result;
    }

    for (int i = 0; i < p.steps; ++i) {
        auto y_next = (p.a * y - p.b * y0 * y0 + p.c * p.u + p.d * std::sin(p.u));
        result.push_back(y_next);
        y0 = y;
        y = y_next;
    }
    return result;
}

