#pragma once

/**
 * @brief Interface for regulator classes that controls temperature
 * according to e(t) - deviation of the output variable y(t) from the desired value w(t).
 */
class IRegulator
{
public:
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    virtual ~IRegulator() = default;

    /**
     * @brief Calculate next u - input warm according to e & t - and returns it.
     * 
     * @param e Deviation of the output variable y(t) from the desired value w(t).
     * @param t Time step at which u is computed.
     * 
     * @return u - Input warm.
     */
    virtual double step(double e, double t) = 0;

protected:
    static constexpr double K { 0.01 }; // Temperature transmit coefficient.

};