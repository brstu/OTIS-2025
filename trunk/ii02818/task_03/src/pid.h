#ifndef PID_H
#define PID_H

#include <vector>

class PID {
private:
    double K;
    double Ti;
    double Td;
    double T0;

    double q0;
    double q1;
    double q2;

    double e_prev1;
    double e_prev2;
    double u_prev;

    double integral;
    double d_filter_alpha = 0.7;
    double d_prev;

public:
    PID(double K, double Ti, double Td, double T0 = 1.0);

    double calculate(double setpoint, double current_value);

    void reset();

    std::vector<double> getCoefficients() const;

    void getParameters(double& K_param, double& Ti_param, double& Td_param) const;
};

#endif