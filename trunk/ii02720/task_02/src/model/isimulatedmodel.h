#pragma once

#include <vector>
#include <memory>

class ISimulatedModel
{
public:
    virtual std::vector<double> simulate(double initialTemp, const double heatInput, int steps) const = 0;
    virtual ~ISimulatedModel() = default;
};
