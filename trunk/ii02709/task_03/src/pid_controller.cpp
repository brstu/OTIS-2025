// src/pid_controller.cpp
#include "pid_controller.h"
#include <cmath>
#include <limits>
#include <algorithm>  // для std::min, std::max

// Вспомогательная функция clamp (работает везде)
static double clamp(double val, double lo, double hi)
{
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

PIDController::PIDController(double k, double ti, double td, double dtt)
    : K(k), Ti(ti), Td(td), dt(dtt),
      u_prev(0.0), e_prev1(0.0), e_prev2(0.0)
{
    // Защита от деления на ноль
    double Ti_safe = (ti > 0.0) ? ti : 1e9;  // если Ti=0 или отрицательное — отключаем интеграл

    // Ключевое: Td=50 при dt=0.1 — это катастрофа (коэффициент 500!)
    // Ограничиваем Td разумным значением: не более 10 шагов дискретизации
    double Td_safe = td;
    if (td > 10.0 * dtt) {
        Td_safe = 10.0 * dtt;  // например, Td=1.0 при dt=0.1
    }

    q0 = K * (1.0 + dt / Ti_safe + Td_safe / dt);
    q1 = -K * (1.0 + 2.0 * Td_safe / dt - dt / Ti_safe);
    q2 = K * (Td_safe / dt);
}

double PIDController::compute(double e)
{
    double du = q0 * e + q1 * e_prev1 + q2 * e_prev2;

    // Жёсткий анти-windup — без этого будет NaN при агрессивных настройках
    du = clamp(du, -50.0, 50.0);
    u_prev += du;
    u_prev = clamp(u_prev, -100.0, 100.0);  // ограничение самого сигнала управления

    // Сохраняем историю
    e_prev2 = e_prev1;
    e_prev1 = e;

    return u_prev;
}

void PIDController::reset()
{
    u_prev = 0.0;
    e_prev1 = 0.0;
    e_prev2 = 0.0;
}