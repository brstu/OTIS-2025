/**
 * @file pid.h
 * @brief Реализация дискретного ПИД-регулятора.
 */

#ifndef II02709_PID_HPP
#define II02709_PID_HPP

#include <array>

/**
 * @brief Специальный тег, обозначающий использование дискретных коэффициентов.
 */
struct DiscreteTag {};

/**
 * @class PID
 * @brief Класс дискретного ПИД-регулятора.
 *
 * Используется рекуррентная формула:
 * u(k) = u(k-1) + q0 * e(k) + q1 * e(k-1) + q2 * e(k-2)
 */
class PID {
public:
    /**
     * @brief Конструктор по непрерывным параметрам.
     * @param K Коэффициент усиления.
     * @param T Время интегрирования.
     * @param TD Время дифференцирования.
     * @param T0 Период дискретизации.
     */
    PID(double K, double T, double TD, double T0);

    /**
     * @brief Конструктор по дискретным коэффициентам q0, q1, q2.
     * @param tag Тег, отличающий этот конструктор.
     * @param q0 Коэффициент q0.
     * @param q1 Коэффициент q1.
     * @param q2 Коэффициент q2.
     * @param u0 Начальное значение управляющего сигнала.
     */
    PID(DiscreteTag tag, double q0, double q1, double q2, double u0 = 0.0);

    /**
     * @brief Сброс внутреннего состояния регулятора.
     * @param u0 Новое начальное значение управления.
     */
    void reset(double u0 = 0.0);

    /**
     * @brief Обновление выходного сигнала u(k).
     * @param e Ошибка e(k).
     * @return Новое значение управляющего воздействия.
     */
    double update(double e);

    /**
     * @brief Получить последнее значение управляющего сигнала.
     */
    double last_u() const { return u_prev; }

    /**
     * @brief Получить дискретные коэффициенты.
     */
    std::array<double,3> q() const { return {q0, q1, q2}; }

private:
    double q0;
    double q1;
    double q2;

    double u_prev;

    double e_prev1;
    double e_prev2;
};

#endif
