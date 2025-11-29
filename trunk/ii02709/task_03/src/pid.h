/**
 * @file pid.h
 * @brief Реализация дискретного ПИД-регулятора в рекуррентной форме.
 */

#ifndef II02709_PID_HPP
#define II02709_PID_HPP

#include <array>

/**
 * @brief Тег, указывающий, что используются дискретные коэффициенты q0,q1,q2.
 */
struct DiscreteTag {};

/**
 * @class PID
 * @brief Дискретный ПИД-регулятор.
 *
 * Формула:
 * u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
 */
class PID {
public:
    /**
     * @brief Конструктор по непрерывным параметрам.
     * @param K Усиление
     * @param T Время интегрирования
     * @param TD Время дифференцирования
     * @param T0 Период дискретизации
     */
    PID(double K, double T, double TD, double T0);

    /**
     * @brief Конструктор по дискретным коэффициентам.
     * @param tag Специальный тег, отличающий этот конструктор
     * @param q0 Коэффициент q0
     * @param q1 Коэффициент q1
     * @param q2 Коэффициент q2
     * @param u0 Начальное значение управления
     */
    PID(DiscreteTag tag, double q0, double q1, double q2, double u0 = 0.0);

    /**
     * @brief Сброс внутренних состояний.
     * @param u0 Начальное значение управления
     */
    void reset(double u0 = 0.0);

    /**
     * @brief Обновление ПИД-регулятора.
     * @param e Ошибка e(k)
     * @return Управляющий сигнал u(k)
     */
    double update(double e);

    /**
     * @brief Получить последнее значение управляющего сигнала.
     */
    double last_u() const { return u_prev; }

    /**
     * @brief Получить коэффициенты q0,q1,q2.
     */
    std::array<double,3> q() const { return {q0, q1, q2}; }

private:
    double q0, q1, q2;
    double u_prev;
    double e_prev1;
    double e_prev2;
};

#endif
