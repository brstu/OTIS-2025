#pragma once

#include "isimulatedmodel.h"
#include <vector>

class LinearModel : public ISimulatedModel
{
public:
    LinearModel(const double a, const double b)
        : m_a(a), m_b(b) 
    {}
    ~LinearModel() override = default;

    std::vector<double> simulate(double y, const double u, int t) const override
    {   
        std::vector<double> results;
        for(int i = 0; i <= t; i++)
        {
            results.push_back(y);
            y = m_a * y + m_b * u;
        } 
        return results;
    }
    
private:
    const double m_a; // Coefficient for previous output (y)
    const double m_b; // Coefficient for input (u)

};