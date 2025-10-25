#include <iostream>
#include <cmath>

struct LinearModelParams
{
    double a; // Coefficient for previous output (y)
    double b; // Coefficient for input (u)
};
struct NonLinearModelParams
{
    double yOffset;      // Initial offset for previous output value (prevY = y - yOffset)
    double uOffset;      // Initial offset for previous input value (prevU = u - uOffset)
    double a;            // Linear coefficient for current output (y)
    double b;            // Nonlinear coefficient for squared previous output (prevY²)
    double c;            // Linear coefficient for input (u)
    double d;            // Nonlinear coefficient for sinusoidal input term
    double u_step;       // Step size for input signal increment
};

void simulateLinear(double y, double u, int t, const LinearModelParams& params)
{
    for (int i = 0; i <= t; i++)
    {
        y = params.a * y + params.b * u;
        std::cout << i << ' ' << y << '\n';
    }
}
void simulateNonLinear(double y, double u, int t, const NonLinearModelParams& params)
{
    double prevY = y - params.yOffset; // calculate prevY to differentiate it from the initial y
    double prevU = u - params.uOffset; // calculate prevU to differentiate it from the initial u
    for (int i = 0; i <= t; i++)
    {
        double nextY = params.a * y - params.b * prevY * prevY + params.c * u + params.d * std::sin(prevU);
        prevU += params.u_step;
        prevY = y;
        y = nextY;
        std::cout << i << ' ' << y << '\n';
    }
}

LinearModelParams createLinearModel()
{
    LinearModelParams params;
    params.a = 0.5;
    params.b = 0.3;
    return params;
}
NonLinearModelParams createNonLinearModel()
{
    NonLinearModelParams params;
    params.yOffset = 0.2;
    params.uOffset = 1;
    params.a = 0.6;
    params.b = 0.4;
    params.c = 0.5;
    params.d = 0.3;
    params.u_step = 0.35;
    return params;
}

int main()
{
    const double y = 1.0; // Initial output value
    const double u = 0.8; // Input signal value
    const int t = 15;     // Number of iterations

    std::cout << "Linear simulation:\n";
    LinearModelParams linearParams = createLinearModel();
    simulateLinear(y, u, t, linearParams);
    std::cout << '\n';

    std::cout << "Nonlinear simulation:\n";
    NonLinearModelParams nonLinearParams = createNonLinearModel();
    simulateNonLinear(y, u, t, nonLinearParams);
    std::cout << '\n';

    return 0;
}