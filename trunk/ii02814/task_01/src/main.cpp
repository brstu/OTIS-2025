#include <iostream>
#include <cmath>

enum ModelType {
    LINEAR,
    NONLINEAR
};

struct LinearModelParams {
    double a;
    double b;
};

struct NonLinearModelParams {
    double a;
    double b;
    double c;
    double d;
    double u_step;
};

struct SimulationParams {
    double y;
    double u;
    int t;
};

SimulationParams getDefaultSimulationParams();

void simulateLinearModel(const SimulationParams& simParams);
LinearModelParams getDefaultLinearParams();

void simulateNonLinearModel(const SimulationParams& simParams);
NonLinearModelParams getDefaultNonLinearParams();

void simulateModel(ModelType type, const SimulationParams& simParams);


int main()
{
    SimulationParams simParams = getDefaultSimulationParams();

    std::cout << "Linear simulation:" << std::endl;
    simulateModel(LINEAR, simParams);
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl;
    simulateModel(NONLINEAR, simParams);
    std::cout << std::endl;

    return 0;
}

SimulationParams getDefaultSimulationParams()
{
    SimulationParams params;
    params.y = 0.6;
    params.u = 60;
    params.t = 10;
    return params;
}

void simulateLinearModel(const SimulationParams& simParams)
{
    LinearModelParams params = getDefaultLinearParams();
    double y = simParams.y;
    double u = simParams.u;
    int t = simParams.t;

    for (int i = 0; i <= t; i++)
    {
        std::cout << i << ' ' << y << std::endl;
        y = params.a * y + params.b * u;
    }
}
LinearModelParams getDefaultLinearParams()
{
    LinearModelParams params;
    params.a = 0.1;
    params.b = 0.8;
    return params;
}


void simulateNonLinearModel(const SimulationParams& simParams)
{
    NonLinearModelParams params = getDefaultNonLinearParams();
    double y = simParams.y;
    double u = simParams.u;
    int t = simParams.t;

    const double yOffset = 0.001;
    const double uOffset = 1;
    double prevY = y - yOffset;
    double prevU = u - uOffset;
    for (int i = 0; i <= t; i++)
    {
        std::cout << i << ' ' << y << std::endl;
        double nextY = params.a * y - params.b * prevY * prevY + params.c * u + params.d * sin(prevU);
        prevU = u;
        u += params.u_step;
        prevY = y;
        y = nextY;
    }
}
NonLinearModelParams getDefaultNonLinearParams()
{
    NonLinearModelParams params;
    params.a = 1;
    params.b = 0.5;
    params.c = 0.9;
    params.d = 2.5;
    params.u_step = 0.01;
    return params;
}

void simulateModel(ModelType type, const SimulationParams& simParams)
{
    switch (type)
    {
    case LINEAR:
        simulateLinearModel(simParams);
        break;
    case NONLINEAR:
        simulateNonLinearModel(simParams);
        break;
    }
}