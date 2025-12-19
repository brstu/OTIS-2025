#pragma once
#include <vector>

class ISimulatedModel
{
public:
    virtual ~ISimulatedModel() = default;
    virtual double calculate(const double inputWarm) = 0;
    virtual std::vector<double> runSimulation(double initialTemp, const double inputWarm, int steps) = 0;
};
