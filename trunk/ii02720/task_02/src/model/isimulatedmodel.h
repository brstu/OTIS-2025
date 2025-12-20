#pragma once

#include <vector>
#include <memory>

class ISimulatedModel
{
public:
    virtual std::vector<double> simulate(double u) = 0;
    virtual ~ISimulatedModel() = default;
    
};

