#pragma once

/**
 * @brief PID controller class.
 *
 * Implements a simple PID controller with parameters:
 * - K: proportional gain
 * - T: integral time
 * - Td: derivative time
 * - T0: sampling period
 */
class PID {
private:
    double K;   ///< Proportional gain
    double T;   ///< Integral time
    double Td;  ///< Derivative time
    double T0;  ///< Sampling period

    double integral = 0.0;   ///< Integral accumulator
    double prevError = 0.0;  ///< Previous error for derivative

public:
    /**
     * @brief Constructor for PID controller.
     * @param K proportional gain
     * @param T integral time
     * @param Td derivative time
     * @param T0 sampling period
     */
    PID(double K, double T, double Td, double T0);

    /**
     * @brief Compute control signal.
     * @param e current error
     * @return control signal u
     */
    double compute(double e);
};