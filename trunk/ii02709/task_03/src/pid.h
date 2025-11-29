/**
 * @file pid.h
 * @brief Реализация дискретного ПИД-регулятора.
 */

#ifndef II02709_PID_HPP
#define II02709_PID_HPP

#include <array>

struct DiscreteTag {};

/**
 * @class PID
 * @brief Дискретный ПИД-регулятор.
 */
class PID {
public:
    PID(double K, double T, double TD, double T0);
    PID(DiscreteTag tag, double q0, double q1, double q2, double u0 = 0.0);

    void reset(double u0 = 0.0);
    double update(double e);

    double last_u() const { return u_prev; }
    std::array<double,3> q() const { return {q0, q1, q2}; }

private:
    double q0;
    double q1;
    double q2;

    double u_prev;
    double e_prev1;
    double e_prev2;
};

#endif
