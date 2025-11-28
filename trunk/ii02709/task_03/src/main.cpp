// src/main.cpp
#include "pid_controller.h"
#include "model.h"
#include <iostream>
#include <iomanip>

int main()
{
    constexpr double dt = 0.1;
    constexpr int    steps = 2000;

    // ВЫБЕРИ ОДИН ИЗ ТРЁХ РЕЖИМОВ:

    // 1. П-регулятор (классический, с ошибкой по статике)
    // const double K = 10.0, Ti = 1e9, Td = 0.0;

    // 2. ПИ-регулятор — мягкий и красивый
    // const double K = 8.0, Ti = 2.0, Td = 0.0;

    // 3. ПИД-регулятор — ЛУЧШИЙ ВАРИАНТ ДЛЯ ОТЧЁТА (аналог рис. 0.4)
    const double K = 10.0;
    const double Ti = 1.0;   // было 0.1 — теперь безопасно
    const double Td = 0.8;   // было 50 — теперь без взрыва и с отличным демпфированием

    PIDController pid(K, Ti, Td, dt);
    Model plant(0.1, 1.0, 0.0, dt);  // a=0.1, b=1.0, T_room=0

    double setpoint = 1.0;

    std::cout << "t\ty\tu\te\n";
    std::cout << std::fixed << std::setprecision(6);

    for (int k = 0; k < steps; ++k)
    {
        double t = k * dt;
        double y = plant.getTemperature();
        double e = setpoint - y;

        double u = pid.compute(e);
        plant.update(u);

        std::cout << t << '\t' << y << '\t' << u << '\t' << e << '\n';
    }

    return 0;
}