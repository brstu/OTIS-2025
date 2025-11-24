/// @file pid.h
/// @brief Реализация дискретного ПИД-регулятора

#ifndef PID_H
#define PID_H

/**
 * @brief Класс дискретного ПИД-регулятора 
 */
class PID {
public:
    /**
     * @brief Конструктор ПИД-регулятора
     * 
     * @param K пропорциональный коэффициент
     * @param T интегральная постоянная
     * @param TD дифференциальная постоянная
     * @param dt шаг дискретизации
     */
    PID(double K, double T, double TD, double dt);

    /**
     * @brief Выполнить один шаг регулятора
     * 
     * @param e ошибка управления
     * @return управляющее воздействие u
     */
    double update(double e);

private:
    double K, T, TD, dt;    ///< параметры ПИД-регулятора
    double e_prev1 = 0.0;   ///< ошибка k-1
    double e_prev2 = 0.0;   ///< ошибка k-2
    double u_prev = 0.0;    ///< предыдущее управление
    double q0, q1, q2;      ///< коэффициенты дискретного ПИД
};

#endif // PID_H
