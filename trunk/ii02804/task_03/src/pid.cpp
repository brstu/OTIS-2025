#include "pid.h"
#include <iostream>

namespace
{
    // вспомогательная функция вычисления приращения
    double computeDelta(
        double k0, double k1, double k2,
        double curErr,
        double prevErr1,
        double prevErr2)
    {
        return (k0 * curErr) +
               (k1 * prevErr1) +
               (k2 * prevErr2);
    }
}

PID::PID(double gain, double ti, double td, double step)
{
    // сохраняем параметры
    K  = gain;
    T  = ti;
    Td = td;
    T0 = step;

    // вычисляем коэффициенты через вспомогательные выражения
    const double invT0 = 1.0 / T0;

    q0 = K * (1.0 + Td * invT0);
    q1 = -K * (1.0 + 2.0 * Td * invT0 - (T0 / T));
    q2 = K * Td * invT0;

    valid = true;
}

double PID::u_calc(double error)
{
    if (!valid) {
        std::cout << "Not valid value of 'q'!\n";
        return 0.0;
    }

    // вычисление приращения
    const double du = computeDelta(
        q0, q1, q2,
        error,
        e_prev_1,
        e_prev_2
    );

    // обновляем управляющее воздействие
    double current_u = u_prev + du;

    // сдвигаем историю ошибок
    e_prev_2 = e_prev_1;
    e_prev_1 = error;

    u_prev = current_u;

    return current_u;
}
