#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PIDController {
private:
    double K;
    double Ti;
    double Td;
    double T;
    double q0;
    double q1;
    double q2;
    double u_prev;
    double e_prev1;
    double e_prev2;

    void calculateCoefficients();

public:
    PIDController(double K = 1.0, double Ti = 0.0, double Td = 0.0, double T = 0.01);
    double calculate(double setpoint, double current_value);
    void reset();
    void setParameters(double K, double Ti, double Td, double T);
    void getParameters(double& K, double& Ti, double& Td, double& T) const;
};

#endif