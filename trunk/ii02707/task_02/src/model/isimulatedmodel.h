#pragma once

#include <vector>
#include <memory>

class ISimulatedModel
{
public:
    virtual std::vector<double> simulate(double y, const double u, int t) const = 0;
    virtual ~ISimulatedModel() = default;
    
};