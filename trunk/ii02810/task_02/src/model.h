#pragma once
#include <iostream>
#include <cmath>
#include <vector>

struct Params {
    float a{}, b{}, c{}, d{}, u{};
    int steps{};

    Params(float a_, float b_, float c_, float d_, float u_, int steps_)
        : a(a_), b(b_), c(c_), d(d_), u(u_), steps(steps_) {}
};


std::vector<float> Linemodel(float y, float u, int steps, float a, float b);
std::vector<float> UnLinemodel(const Params& p, float y, float y0);