#pragma once
#include "isimulatedmodel.hpp"
#include <vector>

/** 
 * @brief Class for representing LinearModel.
 * 
 * This class defines a way to calculate next temperature (y)
 * according to it's formula.
 */ 
class LinearModel : public ISimulatedModel
{
public:
    /**
     * @brief Default constructor for creating LinearModel.
     * 
     * @param a Linear coefficient for previous output (y).
     * @param b Linear coefficient for input (u).
     */
    explicit LinearModel(const double a, const double b)
        : m_a(a), m_b(b) 
    {}
    
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    ~LinearModel() override = default;

    /**
     * @brief Calculates next temperature (y).
     * 
     * Formula for the next temperature (y): 
     * \f[
     * \Large y_{\tau+1} = a y_{\tau} + b u_{\tau}
     * \f]
     * 
     * @param u Input warm.
     * 
     * @return Calculated next temperature (y).
     */
    double step(const double u) override
    {   
        double result = m_a * m_y + m_b * u;
        m_y = result;
        return result; 
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
        std::vector<double> results;
        for(int i = 0; i <= t; i++)
        {
            results.push_back(y);
            y = step(u);
        } 
        return results;
    }
    
private:
    const double m_a; // Linear coefficient for previous output (y).
    const double m_b; // Linear coefficient for input (u).

    double m_y { 0 }; // Initial temperature of the model. 

};