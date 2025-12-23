#include "pid.h"
#include <algorithm>

PIDController::PIDController(double Kp, double Ti, double Td,
                             double dt, double u_min, double u_max)
    : Kp_(Kp), Ti_(Ti), Td_(Td), dt_(dt),
      u_min_(u_min), u_max_(u_max)
{
    if (Ti_ <= 0.0) Ti_ = 1e12;
    updateCoefficients();
}

void PIDController::updateCoefficients()
{
    q0 = Kp_ * (1.0 + Td_ / dt_ + dt_ / (2.0 * Ti_));
    q1 = Kp_ * (dt_ / Ti_ - 2.0 * Td_ / dt_ - 1.0);
    q2 = Kp_ * (Td_ / dt_);
}

double PIDController::calculate(double setpoint, double measured)
{
    double e = setpoint - measured;

    double delta_u = q0 * e + q1 * e_prev1_ + q2 * e_prev2_;
    double u_new = u_prev_ + delta_u;

    bool saturation = false;

    if (u_new > u_max_) {
        u_new = u_max_;
        if (delta_u > 0) saturation = true;
    } 
    else if (u_new < u_min_) {
        u_new = u_min_;
        if (delta_u < 0) saturation = true;
    }

    if (saturation) {
        u_new = u_prev_;
    }

    e_prev2_ = e_prev1_;
    e_prev1_ = e;
    u_prev_  = u_new;

    return u_new;
}

void PIDController::reset()
{
    u_prev_ = e_prev1_ = e_prev2_ = 0.0;
}

void PIDController::setParameters(double Kp, double Ti, double Td)
{
    Kp_ = Kp;
    Ti_ = (Ti <= 0.0 ? 1e12 : Ti);
    Td_ = Td;
    updateCoefficients();
}