#include "test.h"
#include <cmath>

float linear_step(float y1, float u, float a, float b)
{
    return a * y1 + b * u;
}

float nonlinear_step(float y1, float y0, float u, float a, float b, float c, float d)
{
    return a * y1 - b * y0 * y0 + c * u + d * sin(u);
}
