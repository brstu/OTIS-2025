#ifndef PID_H
#define PID_H

#include <array>

/**
 * @class PIDController
 * @brief Discrete PID controller implementation with recurrent algorithm
 * 
 * Implements a digital PID controller using the recurrent form:
 * u[k] = u[k-1] + a0*e[k] + a1*e[k-1] + a2*e[k-2]
 * 
 * Coefficients are computed as:
 * a0 = K * (1 + Ts/Ti + Td/Ts)
 * a1 = -K * (1 + 2*Td/Ts)
 * a2 = K * Td/Ts
 */
class PIDController {
private:
    struct ControllerParameters {
        double K;       ///< Proportional gain
        double Ti;      ///< Integral time constant
        double Td;      ///< Derivative time constant
        double Ts;      ///< Sampling period
    } params;
    
    struct RecurrentCoefficients {
        double a0;      ///< Coefficient for current error
        double a1;      ///< Coefficient for previous error
        double a2;      ///< Coefficient for error two steps back
    } coeffs;
    
    struct ControllerState {
        double ek1;     ///< Error at step k-1
        double ek2;     ///< Error at step k-2
        double uk1;     ///< Control signal at step k-1
    } state;
    
    /**
     * @brief Computes recurrent coefficients based on current parameters
     */
    void computeRecurrentCoefficients();

public:
    /**
     * @brief Constructs a new PIDController object
     * 
     * @param K Proportional gain
     * @param T Integral time constant (Ti)
     * @param Td Derivative time constant
     * @param T0 Sampling period (Ts)
     */
    PIDController(double K, double T, double Td, double T0);
    
    /**
     * @brief Calculates control signal for current step
     * 
     * @param setpoint Desired value (target)
     * @param current_value Measured value (feedback)
     * @return double Control signal u[k]
     */
    double calculate(double setpoint, double current_value);
    
    /**
     * @brief Resets controller state to zero
     * 
     * Clears error history and previous control signal
     */
    void reset();
    
    /**
     * @brief Gets current recurrent coefficients
     * 
     * @return std::array<double, 3> Array [a0, a1, a2]
     */
    std::array<double, 3> getCoefficients() const;
    
    /**
     * @brief Gets controller parameters
     * 
     * @return std::array<double, 4> Array [K, Ti, Td, Ts]
     */
    std::array<double, 4> getParameters() const;
};

#endif // PID_H