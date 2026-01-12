#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <array>

class PIDRegulator {
private:
    struct Gains {
        double P, I, D, Ts;
    } gains;
    
    struct Coefficients {
        double a0, a1, a2;
    } coeffs;
    
    struct Memory {
        double ek1, ek2, uk1;
    } memory;
    
    void computeCoeffs();

public:
    PIDRegulator(double P_gain, double I_time, double D_time, double sample_time);
    double update(double target, double measurement);
    void clear();
    std::array<double, 3> getCoeffs() const;
};

#endif