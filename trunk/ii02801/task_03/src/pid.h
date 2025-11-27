#ifndef PID_H
#define PID_H

class PID {
private:
    double K, T, Td, T0;
    double prev_e;
    double integral;

public:
    PID(double K, double T, double Td, double T0);
    double compute(double e);
};

#endif
