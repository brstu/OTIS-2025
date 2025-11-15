/**
 * @file pid_controller.h
 * @brief Дискретный ПИД-регулятор
 */

#pragma once
#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PIDController {
public:
    PIDController(double K, double T, double TD, double T0);
    double compute(double error);
    void reset();

private:
    double q0, q1, q2;
    double u_prev, e_prev1, e_prev2;
};

#endif // PID_CONTROLLER_H