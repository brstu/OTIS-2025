#pragma once

#include "isimulatedmodel.h"
#include <cmath>
#include <vector>

class NonLinearModel : public ISimulatedModel_2720
{
public:
    NonLinearModel(double a, double b, double c, double d, double initialY)
        : m_a(a), m_b(b), m_c(c), m_d(d), 
          m_prevY(initialY), m_prevPrevY(initialY)
    {}
    ~NonLinearModel() override = default;

    std::vector<double> simulate(double u) override
    {
        std::vector<double> results;
        results.push_back(m_prevY);

        double result = m_a * m_prevY - m_b * m_prevPrevY * m_prevPrevY
                      + m_c * u + m_d * std::sin(m_prevU);
        m_prevPrevY = m_prevY;
        m_prevY = result;
        m_prevU = u;

        return results;
    }

    void reset(double initialY)
    {
        m_prevY = initialY;
        m_prevPrevY = initialY;
        m_prevU = 0;
    }

private:
    const double m_a; // Linear coefficient for current output (y)
    const double m_b; // Nonlinear coefficient for squared previous output
    const double m_c; // Linear coefficient for input (u)
    const double m_d; // Nonlinear coefficient for sinusoidal input term

    double m_prevY;     // Previous output value
    double m_prevPrevY; // Previous previous output value
    double m_prevU = 0; // Previous input value - initialized in-class
};

