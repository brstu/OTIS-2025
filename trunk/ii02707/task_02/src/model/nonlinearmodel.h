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
        double prevY = y - Y_OFFSET; // calculate prevY to diverse it from the initial y
        double prevU = u - U_OFFSET; // calculate prevU to diverse it from the initial u
        std::vector<double> results;
        for(int i = 0; i <= t; i++)
        {
            results.push_back(y);
            prevY = y; // update prevY to current y before calculating nextY
            double nextY = m_a * y - m_b * prevY * prevY + m_c * u + m_d * sin(prevU);
            prevU += u_step;
            y = nextY;
        }
        return results;
    }

private:
    const double m_a; // Linear coefficient for current output (y)
    const double m_b; // Nonlinear coefficient for squared previous output (prevY²)
    const double m_c; // Linear coefficient for input (u)
    const double m_d; // Nonlinear coefficient for sinusoidal input term

    const double Y_OFFSET { 0.001 }; // Initial offset for previous output value (prevY = y - yOffset)
    const int U_OFFSET { 1 }; // Initial offset for previous input value (prevU = u - uOffset)

    const double u_step { 0.5 }; // Step size for input signal increment

};