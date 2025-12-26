#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "pid.h"
#include "model.h"

/**
 * @brief Моделирование PID-регулятора вместе с объектом управления.
 *
 * Результат сохраняется в result.csv (k,w,y,u).
 */

int main() {
    // Настройки модели (можно сменить на нелинейную)
    ModelParams mp{};
    mp.a = 0.8;
    mp.b = 0.05;
    mp.c = 0.0;
    mp.d = 0.0;

    // Настройки ПИД
    PIDParams pidp{};
    pidp.K = 10.0;
    pidp.T = 0.1;
    pidp.Td = 0.01;
    pidp.T0 = 0.1;

    PID pid(pidp);

    const int steps = 400;
    const double target = 10.0;

    std::vector<double> w;
    std::vector<double> y;
    std::vector<double> u;
    y.reserve(steps);
    u.reserve(steps);
    w.reserve(steps);

    double yk = 0.0;

    for (int k = 0; k < steps; ++k) {
        double e = target - yk;
        double uk = pid.update(e);
        double y_next = plant_linear(yk, uk, mp);

        w.push_back(target);
        u.push_back(uk);
        y.push_back(y_next);

        yk = y_next;
    }

    std::ofstream out("result.csv");
    out << "k,w,y,u\n";
    for (size_t i = 0; i < w.size(); ++i) {
        out << i << "," << w[i] << "," << y[i] << "," << u[i] << "\n";
    }
    out.close();

    std::cout << "Simulation finished. result.csv created.\n";
    return 0;
}
