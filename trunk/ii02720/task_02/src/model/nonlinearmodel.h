#pragma once

#include "isimulatedmodel.h"
#include <cmath>
#include <vector>

class NonLinearModel : public ISimulatedModel
{
public:
    NonLinearModel(const double a, const double b, const double c, const double d)
        : m_a(a), m_b(b), m_c(c), m_d(d) 
    {}
    ~NonLinearModel() override = default;

    std::vector<double> simulate(double y, const double u, int t) const override
    {    
        double prevY = y;
        double prevU = 0;
        std::vector<double> results;
        for(int i = 0; i <= t; i++)
        {
            results.push_back(y);
            double nextY = m_a * y - m_b * prevY * prevY + m_c * u + m_d * sin(prevU);
            prevY = y;
            prevU = u;
            y = nextY;
        }
        return results;
    }

private:
    const double m_a; // Linear coefficient for current output (y)
    const double m_b; // Nonlinear coefficient for squared previous output (prevY²)
    const double m_c; // Linear coefficient for input (u)
    const double m_d; // Nonlinear coefficient for sinusoidal input term

};

