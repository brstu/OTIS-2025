#pragma once

/**
 * @brief Дискретный ПИД-регулятор в рекуррентной (velocity) форме
 */
class PIDController {
public:
    PIDController(double Kp = 1.0, double Ti = 1e12, double Td = 0.0,
                  double dt = 1.0, double u_min = 0.0, double u_max = 100.0);

    double calculate(double setpoint, double measured);
    void reset();
    void setParameters(double Kp, double Ti, double Td);

private:
    void updateCoefficients();

    double Kp_, Ti_, Td_, dt_;
    double u_min_, u_max_;

    double q0{}, q1{}, q2{};
    double u_prev_ = 0.0;
    double e_prev1_ = 0.0, e_prev2_ = 0.0;
};