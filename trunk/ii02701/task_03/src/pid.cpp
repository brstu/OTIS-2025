#include "pid.h"

void initPID(PID& pid, double q0, double q1, double q2)
{
    pid.q0 = q0;
    pid.q1 = q1;
    pid.q2 = q2;

    pid.u_prev = 0.0;
    pid.e_prev1 = 0.0;
    pid.e_prev2 = 0.0;
}

double updatePID(PID& pid, double e)
{
    double du =
        pid.q0 * e +
        pid.q1 * pid.e_prev1 +
        pid.q2 * pid.e_prev2;

    double u = pid.u_prev + du;

    pid.e_prev2 = pid.e_prev1;
    pid.e_prev1 = e;
    pid.u_prev = u;

    return u;
}