#include "modelsimulation.h"

SimulationParams getDefaultSimulationParams()
{
    SimulationParams params;
    params.y = 0.6; // Initial output value
    params.u = 60;  // Input signal value
    params.t = 5;  // Simulation time steps
    return params;
}

std::vector<double> simulateLinearModel(const SimulationParams& simParams)
{
    LinearModelParams params = getDefaultLinearParams();
    double y = simParams.y;
    std::vector<double> results;

    for (int i = 0; i <= simParams.t; i++)
    {
        results.push_back(y);
        y = params.a * y + params.b * simParams.u;
    }
    
    return results;
}

LinearModelParams getDefaultLinearParams()
{
    LinearModelParams params;
    params.a = 0.1; // Coefficient for previous output (y)
    params.b = 0.8; // Coefficient for input (u)
    return params;
}

std::vector<double> simulateNonLinearModel(const SimulationParams& simParams)
{
    NonLinearModelParams params = getDefaultNonLinearParams();
    double y = simParams.y;
    double u = simParams.u;
    std::vector<double> results;

    // Initialize previous output and input values using offsets.
    // The offsets (yOffset and uOffset) represent the difference between the initial state and the previous state,
    // allowing the nonlinear model to start with a defined history for y and u.
    double prevY = y - params.yOffset;
    double prevU = u - params.uOffset;

    for (int i = 0; i <= simParams.t; i++)
    {
        results.push_back(y);
        // Compute nextY using previous values
        double nextY = params.a * y - params.b * prevY * prevY + params.c * u + params.d * sin(prevU);
        // Update all 'prev' variables first
        prevY = y;
        prevU = u;
        y = nextY;
        u += params.u_step;
    }
    
    return results;
}

NonLinearModelParams getDefaultNonLinearParams()
{
    NonLinearModelParams params;
    params.yOffset = 0.001;  // Small offset for previous output to avoid singularities in nonlinear terms.
    params.uOffset = 1;      // Offset for previous input to ensure nonzero argument in sinusoidal term.
    params.a = 1;            // Linear coefficient for current output (y)
    params.b = 0.5;          // Nonlinear coefficient for squared previous output (prevY²)
    params.c = 0.9;          // Linear coefficient for input (u)
    params.d = 2.5;          // Nonlinear coefficient for sinusoidal input term
    params.u_step = 0.01;    // Step size for input signal increment
    return params;
}