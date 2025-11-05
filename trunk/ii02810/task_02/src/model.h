#pragma once
#include <iostream>
#include <cmath>
#include <vector>

struct Params {
    float a;
    float b;
    float c;
    float d;
    float u;
    int steps;
};

std::vector<float> Linemodel(float y, float u, int steps, float a, float b);
std::vector<float> UnLinemodel(const Params& p, float y, float y0);