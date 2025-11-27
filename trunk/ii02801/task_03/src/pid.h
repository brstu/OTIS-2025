#ifndef PID_H
#define PID_H

class PID {
private:
    double K;
    double T;
    double Td;
    double T0;
    double prev_e = 0;
    double integral = 0;

public:
    PID(double K, double T, double Td, double T0);
    double compute(double e);
};

#endif
