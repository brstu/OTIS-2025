#pragma once

#include <vector>
#include <memory>

class ISimulatedModel_2720
{
public:
    virtual std::vector<double> simulate(double u) = 0;
    virtual ~ISimulatedModel_2720() = default;
};