#pragma once

#include "isimulatedmodel.h"
#include <vector>

class LinearModel : public ISimulatedModel_2720
{
public:
    LinearModel(double a, double b, double initialY)
        : m_a(a), m_b(b), m_prevY(initialY) 
    {}
    ~LinearModel() override = default;

    std::vector<double> simulate(double u) override
    {   
        std::vector<double> results;
        results.push_back(m_prevY);
        m_prevY = m_a * m_prevY + m_b * u;
        return results;
    }
    
    void reset(double initialY) 
    {
        m_prevY = initialY;
    }

private:
    const double m_a; // Coefficient for previous output (y)
    const double m_b; // Coefficient for input (u)
    double m_prevY;   // Previous output value
};

