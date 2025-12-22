#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "pid.h"
#include "control_object.h"

/**
 * @file main.cpp
 * @brief Основная программа моделирования ПИД-регулятора.
 *
 * Эта программа моделирует дискретный ПИД-регулятор, применяемый к динамической системе второго порядка,
 * представляющей объект управления. Объект моделируется передаточной функцией:
 * G(s) = K / (T^2 s^2 + 2 ξ T s + 1)
 *
 * Моделирование использует метод Эйлера для дискретизации непрерывной модели.
 */

/**
 * @brief Основная функция моделирования.
 *
 * Моделирует управление ПИД для разных изменений уставки и выводит данные в CSV для построения графиков.
 */
int main() {
    // Параметры ПИД (из примера: П-регулятор, ПИ, ПИД)
    // Здесь используется пример ПИД: K=10, Ti=0.1, Td=50, но Td=50 кажется большим, при необходимости скорректировать
    // Примечание: Td=50 при малом Ts может вызвать проблемы, используйте меньшее Td или проверьте.
    double K_pid = 10.0;
    double Ti = 0.1;
    double Td = 0.05; // Скорректировано для стабильности, оригинальное 50 может быть опечаткой или проблемой с единицами
    double Ts = 0.01; // Время дискретизации TO

    // Параметры объекта (из примера варианта)
    double K_obj = 3.0;
    double T_obj = 0.1;
    double xi = 1.0;

    PID pid(K_pid, Ti, Td, Ts);
    ControlObject obj(K_obj, T_obj, xi);

    // Параметры моделирования
    double sim_time = 10.0; // Общее время моделирования
    int steps = static_cast<int>(sim_time / Ts);
    std::vector<double> time(steps);
    std::vector<double> setpoint(steps);
    std::vector<double> y_out(steps);
    std::vector<double> u_out(steps);
    std::vector<double> e_out(steps);

    double current_setpoint = 0.0;
    double current_y = 0.0;

    std::ofstream output("simulation_results.csv");
    output << "time,setpoint,y,u,e\n";

    for (int k = 0; k < steps; ++k) {
        time[k] = k * Ts;

        // Изменение уставки в определенные моменты времени для разных заданий
        if (time[k] < 2.0) {
            current_setpoint = 1.0; // Первая уставка температуры
        } else if (time[k] < 5.0) {
            current_setpoint = 2.0; // Вторая
        } else if (time[k] < 8.0) {
            current_setpoint = 1.5; // Третья
        } else {
            current_setpoint = 0.5; // Четвертая
        }

        double e = current_setpoint - current_y;
        double u = pid.compute(e);
        current_y = obj.update(u, Ts);

        setpoint[k] = current_setpoint;
        y_out[k] = current_y;
        u_out[k] = u;
        e_out[k] = e;

        output << time[k] << "," << setpoint[k] << "," << y_out[k] << "," << u_out[k] << "," << e_out[k] << "\n";
    }

    output.close();
    std::cout << "Моделирование завершено. Результаты сохранены в simulation_results.csv" << std::endl;

    return 0;
}