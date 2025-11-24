/// @file pid.h
/// @brief Класс ПИД-регулятора

#ifndef PID_H
#define PID_H

/// Класс ПИД-регулятора
class PID {
public:
    PID(double K, double T, double TD, double dt);

    double update(double e);

private:
    double K, T, TD, dt;
    double e_prev1 = 0.0;
    double e_prev2 = 0.0;
    double u_prev = 0.0;
    double q0, q1, q2;
};

#endif // PID_H
