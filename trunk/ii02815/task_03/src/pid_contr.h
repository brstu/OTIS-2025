/**
 * @file pid_contr.h
 * @brief Класс дискретного PID-регулятора 
 */

#pragma once

/**
 * @class PID
 * @brief Ипользует текущую формулу:
 * u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
 */
class PID {
private:
    double q0;          ///< Коэффициент при текущей ошибке
    double q1;          ///< Коэффициент при предыдущей ошибке
    double q2;          ///< Коэффициент при ошибке два шага назад
    double u_prev=0.0;      ///< Предыдущее воздействие u(k-1)
    double e_prev1=0.0;     ///< Предыдущая ошибка e(k-1)
    double e_prev2=0.0;     ///< Ошибка два шага назад e(k-2)

public:
    /**
     * @brief Конструктор с коэфициентами
     */
    PID(double q0, double q1, double q2);
    
    /**
     * @brief Конструктор PID-регулятора
     * @param K Коэффициент усиления
     * @param Ti Время интегрирования
     * @param Td Время дифференцирования
     * @param T0 Шаг дискретизации
     */
    PID(double K, double Ti, double Td, double T0);
    
    /**
     * @brief Вычисляет новое воздействие
     * @param e текущая ошибка
     * @return воздействие u(k)
     */
    double compute(double e);
    
    /**
     * @brief сброс состояния регулятора
     */
    void reset();
};