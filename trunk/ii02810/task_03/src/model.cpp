#include "model.h"
#include <cmath>

HeaterModel::HeaterModel(double K, double T, double tau, double dt)
    : K_(K), T_(T), tau_(tau), dt_(dt)
{
    delay_steps_ = static_cast<size_t>(std::ceil(tau_ / dt_));
    u_delay_line_.resize(delay_steps_, 0.0);
}

void HeaterModel::reset()
{
    y_ = 0.0;
    std::fill(u_delay_line_.begin(), u_delay_line_.end(), 0.0);
}

double HeaterModel::step(double u)
{
    double u_delayed = u_delay_line_.front();
    u_delay_line_.push_back(u);
    u_delay_line_.erase(u_delay_line_.begin());

    double alpha = std::exp(-dt_ / T_);
    y_ = y_ * alpha + K_ * u_delayed * (1.0 - alpha);

    return y_;
}