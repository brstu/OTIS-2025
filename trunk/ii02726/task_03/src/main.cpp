#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "pid.h"
#include "plant.h"
#include "sim.h"

/**
 * @brief Пример запуска симуляции: ступенчатое задание и линейная/нелинейная модели.
 */
int main(int argc, char** argv) {
    int steps = 1000;
    double T0 = 0.1;

    PIDConfig cfg;
    cfg.K = 2.0;
    cfg.T = 10.0;
    cfg.TD = 1.0;
    cfg.T0 = T0;
    cfg.u_max = 100.0;
    cfg.anti_windup = true;

    auto w_func = [](int k) {
        if (k < 20) return 0.0;
        return 80.0;
    };

    double a = 0.95;
    double b = 0.05;

    auto plant_step_linear = [a, b](int /*k*/, double u_k, double y_k1, double /*y_k2*/) {
        return a * y_k1 + b * u_k;
    };

    abcd nl{1.0, 0.0005, 0.05, 0.01};
    auto plant_step_nonlinear = [nl](int /*k*/, double u_k, double y_k1, double y_k2) {
        return nl.a * y_k1 - nl.b * y_k2 * y_k2 + nl.c * u_k + nl.d * std::sin(u_k);
    };

    auto res_lin = run_simulation(steps, T0, cfg, plant_step_linear, w_func, 0.0, 0.0);
    auto res_nl  = run_simulation(steps, T0, cfg, plant_step_nonlinear, w_func, 0.0, 0.0);

    save_csv("doc/data/run_linear.csv", res_lin);
    save_csv("doc/data/run_nonlinear.csv", res_nl);

    std::cout << "Simulation finished. CSV saved to doc/data/.\n";
    return 0;
}
