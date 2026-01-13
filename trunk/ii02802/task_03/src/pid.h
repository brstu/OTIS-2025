#ifndef PID_H
#define PID_H

/**
 * @class PID
 * @brief Класс дискретного ПИД-регулятора.
 *
 * Реализует рекуррентную форму дискретного ПИД-регулятора:
 * u(k) = u(k-1) + q0 * e(k) + q1 * e(k-1) + q2 * e(k-2)
 */
class PID {
private:
    double q0;      ///< Коэффициент q0
    double q1;      ///< Коэффициент q1
    double q2;      ///< Коэффициент q2
    double e_prev1 = 0.0;  ///< e(k-1) — инициализация по умолчанию
    double e_prev2 = 0.0;  ///< e(k-2) — инициализация по умолчанию
    double u_prev = 0.0;   ///< u(k-1) — инициализация по умолчанию

public:
    /**
     * @brief Конструктор ПИД-регулятора.
     * @param K Коэффициент пропорциональности.
     * @param Ti Постоянная времени интегрирования.
     * @param Td Постоянная времени дифференцирования.
     * @param Ts Время дискретизации (TO).
     */
    PID(double K, double Ti, double Td, double Ts);

    /**
     * @brief Вычисление управляющего сигнала.
     * @param e Текущая ошибка e(k).
     * @return Управляющий сигнал u(k).
     */
    double compute(double e);
};

#endif // PID_H