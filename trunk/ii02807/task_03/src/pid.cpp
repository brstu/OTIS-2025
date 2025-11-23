#include "pid.h"

/**
 * @brief Constructor implementation for PID controller.
 */
PID::PID(double K, double T, double Td, double T0)
    : K(K), T(T), Td(Td), T0(T0), integral(0.0), prevError(0.0) {}

/**
 * @brief Compute control signal using PID formula.
 *
 * u = K * ( e + (T0/T) * integral + (Td/T0) * derivative )
 *
 * @param e current error
 * @return control signal u
 */
double PID::compute(double e) {
    // Integral term
    integral += e * T0;

    // Derivative term
    double derivative = (e - prevError) / T0;

    // PID output
    double u = K * (e + (integral / T) + (Td * derivative));

    prevError = e;
    return u;
}
