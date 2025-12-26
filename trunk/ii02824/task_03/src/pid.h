#pragma once

/**
 * @brief Структура коэффициентов PID-регулятора
 */
struct pid1_coeffs
{
    const double K1;  ///< коэффициент передачи
    const double T1;  ///< постоянная интегрирования
    const double Td1; ///< постоянная дифференцирования
    const double T01; ///< шаг

    /**
     * @brief Конструктор коэффициентов PID-регулятора
     * @param K1 коэффициент передачи
     * @param T1 постоянная интегрирования
     * @param Td1 постоянная дифференцирования
     * @param T01 шаг
     */
    pid1_coeffs(double K1, double T1, double Td1, double T01);
};

/**
 * @brief Класс PID-регулятора
 */
class pid1
{
private:
    pid1_coeffs coeffs;  ///< коэффициенты PID-регулятора   

    double q0;          ///< параметр PID-регулятора
    double q1;          ///< параметр PID-регулятора
    double q2;          ///< параметр PID-регулятора

    double u_prev;      ///< предыдущее значение управляющего воздействия
    double e_prev;      ///< предыдущее значение отклонения
    double e_prev_prev; ///< предпредыдущее значение отклонения

public:
    
    pid1(const pid1_coeffs& coeffs, double _u, double _e, double __e);

    double process(double e);
};