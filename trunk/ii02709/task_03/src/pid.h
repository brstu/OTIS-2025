/**
 * @file pid.h
 * @brief Дискретный ПИД-регулятор (рекуррентная форма).
 *
 * Формула:
 *   u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
 */

#ifndef II02709_PID_HPP
#define II02709_PID_HPP

#include <array>

/**
 * @brief Тег-конструктор для случая, когда задаются дискретные коэффициенты.
 */
struct DiscreteTag {};

/**
 * @class PID
 * @brief Дискретный ПИД-регулятор.
 */
class PID {
public:
    /**
     * @brief Конструктор по непрерывным параметрам.
     * @param K Усиление.
     * @param T Время интегрирования.
     * @param TD Время дифференцирования.
     * @param T0 Период дискретизации.
     */
    PID(double K, double T, double TD, double T0);

    /**
     * @brief Конструктор по дискретным коэффициентам q0,q1,q2.
     * @param tag Тег, отличающий этот конструктор.
     * @param q0 Коэффициент q0.
     * @param q1 Коэффициент q1.
     * @param q2 Коэффициент q2.
     * @param u0 Начальное значение управляющего сигнала.
     */
    PID(DiscreteTag tag, double q0, double q1, double q2, double u0 = 0.0);

    /**
     * @brief Сброс внутреннего состояния.
     * @param u0 Новое начальное значение управления.
     */
    void reset(double u0 = 0.0);

    /**
     * @brief Обновление ПИД-регулятора (одно тактование).
     * @param e Текущая ошибка e(k).
     * @return Значение управляющего сигнала u(k).
     */
    double update(double e);

    /**
     * @brief Возвращает последнее значение управляющего сигнала.
     */
    double last_u() const { return u_prev; }

    /**
     * @brief Возвращает массив дискретных коэффициентов {q0,q1,q2}.
     */
    std::array<double,3> q() const { return {q0, q1, q2}; }

private:
    double q0 = 0.0;
    double q1 = 0.0;
    double q2 = 0.0;

    double u_prev = 0.0;

    double e_prev1 = 0.0;
    double e_prev2 = 0.0;
};

#endif // II02709_PID_HPP
