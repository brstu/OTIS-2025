#pragma once
#include <vector>

/**
 * @brief Модель объекта управления – нагреватель (1-й порядок + чистое запаздывание)
 */
class HeaterModel {
public:
    explicit HeaterModel(double K = 2.0, double T = 150.0, double tau = 20.0, double dt = 1.0);

    double step(double u);
    void reset();
    double getTemperature() const { return y_; }

private:
    double K_   = 0.0;
    double T_   = 0.0;
    double tau_ = 0.0;
    double dt_  = 0.0;

    double y_ = 0.0;
    std::vector<double> u_delay_line_;
    size_t delay_steps_;
};