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
    double yOffset;
    double uOffset;
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
    params.y = 0.6; // Initial output value
    params.u = 60;  // Input signal value
    params.t = 10;  // Simulation time steps
    return params;
}

void simulateLinearModel(const SimulationParams& simParams)
{
    LinearModelParams params = getDefaultLinearParams();
    double y = simParams.y;

    for (int i = 0; i <= simParams.t; i++)
    {
        std::cout << i << ' ' << y << std::endl;
        y = params.a * y + params.b * simParams.u;
    }
}

LinearModelParams getDefaultLinearParams()
{
    LinearModelParams params;
    params.a = 0.1; // Coefficient for previous output (y)
    params.b = 0.8; // Coefficient for input (u)
    return params;
}

void simulateNonLinearModel(const SimulationParams& simParams)
{
    NonLinearModelParams params = getDefaultNonLinearParams();
    double y = simParams.y;
    double u = simParams.u;
    int t = simParams.t;

    // Initialize previous output and input values using offsets.
    // The offsets (yOffset and uOffset) represent the difference between the initial state and the previous state,
    // allowing the nonlinear model to start with a defined history for y and u.
    double prevY = y - params.yOffset;
    double prevU = u - params.uOffset;

    for (int i = 0; i <= t; i++)
    {
        std::cout << i << ' ' << y << std::endl;
        // Update all 'prev' variables first
        prevY = y;
        prevU = u;
        // Compute nextY using previous values
        double nextY = params.a * y - params.b * prevY * prevY + params.c * u + params.d * sin(prevU);
        // Update current variables
        y = nextY;
        u += params.u_step;
    }
}

NonLinearModelParams getDefaultNonLinearParams()
{
    NonLinearModelParams params;
    params.yOffset = 0.001;  // Offset subtracted from current output to compute previous output (prevY = y - yOffset)
    params.uOffset = 1;      // Offset subtracted from current input to compute previous input (prevU = u - uOffset)
    params.a = 1;            // Linear coefficient for current output (y)
    params.b = 0.5;          // Nonlinear coefficient for squared previous output (prevY²)
    params.c = 0.9;          // Linear coefficient for input (u)
    params.d = 2.5;          // Nonlinear coefficient for sinusoidal input term
    params.u_step = 0.01;    // Step size for input signal increment
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
    default:
        std::cerr << "Error: Invalid ModelType value passed to simulateModel." << std::endl;
        break;
    }
}