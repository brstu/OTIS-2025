#ifndef SIM_H
#define SIM_H

#include <vector>
#include <functional>
#include <string>
#include "pid.h"

/**
 * @brief Профиль задания w(k) (кусочно‑постоянный или иной).
 */
using SetpointFunc = std::function<double(int)>;

/**
 * @brief Результаты одного прогона симуляции.
 */
struct SimResult {
    double T0{0.1};
    std::vector<double> t;  ///< Время
    std::vector<double> w;  ///< Задание
    std::vector<double> y;  ///< Выход объекта
    std::vector<double> u;  ///< Управляющее воздействие
    std::vector<double> e;  ///< Ошибка
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
SimResult run_simulation(int steps, double T0, const PIDConfig& pid,
                         const std::function<double(int, double, double, double)>& plant_step,
                         const SetpointFunc& w_func,
                         double y0 = 0.0, double y1 = 0.0);

/**
 * @brief Сохранить результаты в CSV.
 *
 * @param path Путь к файлу.
 * @param r Результаты симуляции.
 */
void save_csv(const std::string& path, const SimResult& r);

#endif // SIM_H
