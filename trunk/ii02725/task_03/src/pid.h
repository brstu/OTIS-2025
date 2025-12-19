#ifndef PID_H
#define PID_H

#include <array>

struct DiscreteTag {};

class PID {
public:
    PID(double K, double T, double TD, double T0);
    PID(DiscreteTag, double q0, double q1, double q2, double u0 = 0.0);

    void reset(double u0 = 0.0);
    double update(double e);

    double last_u() const { return u_prev; }
    std::array<double,3> q() const { return {q0, q1, q2}; }

private:
    double q0{0.0};
    double q1{0.0};
    double q2{0.0};

    double u_prev{0.0};
    double e_prev1{0.0};
    double e_prev2{0.0};
};

#endif