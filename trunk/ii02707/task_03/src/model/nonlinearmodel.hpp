#pragma once
#include "isimulatedmodel.hpp"
#include <vector>
#include <cmath>

/** 
 * @brief Class for representing NonLinearModel.
 * 
 * This class defines a way to calculate next temperature (y)
 * according to it's formula.
 */ 
class NonLinearModel : public ISimulatedModel
{
public:
    /**
     * @brief Default constructor for creating NonLinearModel.
     * 
     * @param a Nonlinear coefficient for current output (y).
     * @param b Nonlinear coefficient for squared previous output (prevY²).
     * @param c Nonlinear coefficient for input (u).
     * @param d Nonlinear coefficient for sinusoidal input term.
     */
    explicit NonLinearModel(const double a, const double b, const double c, const double d)
        : m_a(a), m_b(b), m_c(c), m_d(d) 
    {}

    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    ~NonLinearModel() override = default;

    /**
     * @brief Calculates next temperature (y).
     * 
     * Formula for the next temperature (y): 
     * \f[
     * \Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})
     * \f]
     * 
     * @param u Input warm.
     * 
     * @return Calculated next temperature (y).
     */
    double step(const double u) override
    {     
        double nextY = m_a * m_y - m_b * m_prevY * m_prevY + m_c * u + m_d * sin(m_prevU);
        m_prevY = m_y; // update m_prevY to current y before calculating nextY
        m_y = nextY;
        m_prevU = u;
        return nextY;
    }

    /**
     * @brief Computes a vector of calculated temperatures & returns it according to y, u, t.
     * 
     * @param y Initial temperature.
     * @param u Input warm.
     * @param t Time step at which vector of calculated temperatures is computed.
     * 
     * @return A vector of calculated temperatures.
     */
    std::vector<double> simulate(double y, const double u, int t) override
    {  
        m_prevY = y - y_offset; // initialize m_prevY to differentiate it from the initial y  
        std::vector<double> results;
        for(int i = 0; i <= t; i++)
        {
            m_prevU = u - u_offset; // calculate m_prevU to differentiate it from the initial u
            m_prevU += i*u_step;
            results.push_back(y);
            y = step(u);
        }
        return results;
    }

private:
    const double m_a; // Nonlinear coefficient for current output (y).
    const double m_b; // Nonlinear coefficient for squared previous output (prevY²).
    const double m_c; // Nonlinear coefficient for input (u).
    const double m_d; // Nonlinear coefficient for sinusoidal input term.

    const double y_offset { 0.001 }; // Initial offset for previous output value (prevY = y - yOffset).
    const int u_offset { 1 }; // Initial offset for previous input value (prevU = u - uOffset).
    const double u_step { 0.5 }; // Step size for input signal increment.

    double m_prevY { 0 }; // initialize with 0
    double m_prevU { 0 }; // initialize with 0

    double m_y { 0 }; // Initial temperature of the model. 
};