#pragma once
#include <vector>

/** 
 * @brief Interface for simulated models classes.
 * 
 * This abstract class defines a way to calculate next temperature (y)
 * according to the model's formula.
 */ 
class ISimulatedModel
{
public:
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    virtual ~ISimulatedModel() = default;

    /**
     * @brief Calculates next temperature (y) according to the model's formula and returns it.
     * 
     * @param u Input warm.
     * 
     * @return Calculated next temperature (y).
     */
    virtual double step(const double u) = 0;

    /**
     * @brief Computes a vector of calculated temperatures & returns it according to y, u, t.
     * 
     * @param y Initial temperature.
     * @param u Input warm.
     * @param t Time step at which vector of calculated temperatures is computed.
     * 
     * @return A vector of calculated temperatures.
     */
    virtual std::vector<double> simulate(double y, const double u, int t) = 0;

};