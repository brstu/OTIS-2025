#include "pid.h"
#include <algorithm>
#include <cmath>

/**
 * @brief Внутреннее вычисление коэффициентов q0, q1, q2 по cfg_.
 */
void PID::compute_q() {
    const double K  = cfg_.K;
    const double T  = cfg_.T;
    const double TD = cfg_.TD;
    const double T0 = cfg_.T0;

    const bool integral_off = !std::isfinite(T) || (T <= 0.0);
    const double T_term = integral_off ? 0.0 : (T0 / T);

    q0_ = K * (1.0 + TD / T0);
    q1_ = -K * (1.0 + 2.0 * TD / T0 - T_term);
    q2_ = K * (TD / T0);
}

PID::PID(const PIDConfig& cfg) : cfg_(cfg) {
    compute_q();
    reset();
}

void PID::reset(double u0, double e_1, double e_2) {
    u_k_  = u0;
    e_k_  = e_1;
    e_k1_ = e_1;
    e_k2_ = e_2;
}

double PID::saturate(double v) const {
    if (cfg_.u_max > 0.0) {
        v = std::clamp(v, -cfg_.u_max, cfg_.u_max);
    }
    return v;
}

double PID::step(double e_k) {
    e_k2_ = e_k1_;
    e_k1_ = e_k_;
    e_k_  = e_k;

    double delta_u = q0_ * e_k_ + q1_ * e_k1_ + q2_ * e_k2_;
    double u_next  = u_k_ + delta_u;

    if (cfg_.anti_windup && cfg_.u_max > 0.0) {
        u_next = saturate(u_next);
    }

    u_k_ = u_next;
    return u_k_;
}

void PID::get_q(double& q0, double& q1, double& q2) const {
    q0 = q0_;
    q1 = q1_;
    q2 = q2_;
}
