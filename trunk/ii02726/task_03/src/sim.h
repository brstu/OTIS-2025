#ifndef SIM_H
#define SIM_H

#include <vector>
#include <string>
#include "pid.h"

/**
 * @brief Результаты одного прогона симуляции.
 */
struct SimResult {
    double T0{0.1};
    std::vector<double> t; 
    std::vector<double> w;  
    std::vector<double> y;
    std::vector<double> u;
    std::vector<double> e;
};

/**
 * @brief Запуск симуляции ПИД+объект по шагам.
 *
 * @param steps Количество шагов.
 * @param T0 Шаг дискретизации.
 * @param pid Конфигурация ПИД‑регулятора.
 * @param plant_step Функция шага объекта: (k, u[k], y[k-1], y[k-2]) -> y[k].
 * @param w_func Профиль задания w(k).
 * @param y0,y1 Начальные значения выхода.
 * @return Результат симуляции (векторы t,w,y,u,e).
 */
template <typename PlantStep, typename WFunc>
SimResult run_simulation(int steps, double T0, const PIDConfig& pid,
                         PlantStep plant_step,
                         WFunc w_func,
                         double y0 = 0.0, double y1 = 0.0) {
    SimResult res;
    res.T0 = T0;
    res.t.resize(steps);
    res.w.resize(steps);
    res.y.resize(steps);
    res.u.resize(steps);
    res.e.resize(steps);

    PID pid_ctrl(pid);
    pid_ctrl.reset(0.0, 0.0, 0.0);

    if (steps > 0) {
        res.t[0] = 0.0;
        res.w[0] = w_func(0);
        res.y[0] = y0;
        res.e[0] = res.w[0] - res.y[0];
        res.u[0] = pid_ctrl.step(res.e[0]);
    }
    if (steps > 1) {
        res.t[1] = T0;
        res.w[1] = w_func(1);
        res.y[1] = y1;
        res.e[1] = res.w[1] - res.y[1];
        res.u[1] = pid_ctrl.step(res.e[1]);
    }

    for (int k = 2; k < steps; ++k) {
        res.t[k] = k * T0;
        res.w[k] = w_func(k);
        res.e[k] = res.w[k] - res.y[k - 1];
        res.u[k] = pid_ctrl.step(res.e[k]);
        res.y[k] = plant_step(k, res.u[k], res.y[k - 1], res.y[k - 2]);
    }

    return res;
}

/**
 * @brief Сохранить результаты в CSV.
 */
void save_csv(const std::string& path, const SimResult& r);

#endif
