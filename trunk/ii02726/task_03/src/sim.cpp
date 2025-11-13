#include "sim.h"
#include <fstream>
#include <iomanip>

SimResult run_simulation(int steps, double T0, const PIDConfig& pid_cfg,
                         const std::function<double(int, double, double, double)>& plant_step,
                         const SetpointFunc& w_func,
                         double y0, double y1) {
    SimResult res;
    res.T0 = T0;
    res.t.resize(steps);
    res.w.resize(steps);
    res.y.resize(steps);
    res.u.resize(steps);
    res.e.resize(steps);

    PID pid(pid_cfg);
    pid.reset(0.0, 0.0, 0.0);

    // Инициализация
    if (steps > 0) {
        res.t[0] = 0.0;
        res.w[0] = w_func(0);
        res.y[0] = y0;
        res.e[0] = res.w[0] - res.y[0];
        res.u[0] = pid.step(res.e[0]);
    }
    if (steps > 1) {
        res.t[1] = T0;
        res.w[1] = w_func(1);
        res.y[1] = y1;
        res.e[1] = res.w[1] - res.y[1];
        res.u[1] = pid.step(res.e[1]);
    }

    for (int k = 2; k < steps; ++k) {
        res.t[k] = k * T0;
        res.w[k] = w_func(k);
        res.e[k] = res.w[k] - res.y[k - 1]; // ошибка между заданием и прошлым выходом
        res.u[k] = pid.step(res.e[k]);
        res.y[k] = plant_step(k, res.u[k], res.y[k - 1], res.y[k - 2]);
    }

    return res;
}

void save_csv(const std::string& path, const SimResult& r) {
    std::ofstream f(path);
    f << std::fixed << std::setprecision(6);
    f << "t,w,y,u,e\n";
    for (size_t i = 0; i < r.t.size(); ++i) {
        f << r.t[i] << "," << r.w[i] << "," << r.y[i] << "," << r.u[i] << "," << r.e[i] << "\n";
    }
}
