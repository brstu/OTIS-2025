#pragma once
#include <cmath>
#include <vector>

struct Params {
    float a{};
    float b{};
    float c{};
    float d{};
    float u{};
    int steps{};

    Params(float a_, float b_, float c_, float d_, float u_, int steps_)
        : a(a_), b(b_), c(c_), d(d_), u(u_), steps(steps_) {}
};


std::vector<float> Linemodel(float y, float u, int steps, float a, float b);
std::vector<float> UnLinemodel(const Params& p, float y, float y0);