#pragma once
#include <iostream>
#include <cmath>

struct Params {
    float a;
    float b;
    float c;
    float d;
    float u;
    int steps;
};

void Linemodel(float y, float u, int steps, float a, float b, int i = 1);
void UnLinemodel(const Params& p, float y, float y0, int i = 1);