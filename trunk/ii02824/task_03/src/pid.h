#pragma once

/**
 * @brief Структура коэффициентов PID-регулятора
 */
struct pid_coeffs
{
    const double K1;  ///< коэффициент передачи
    const double T1;  ///< постоянная интегрирования
    const double Td1; ///< постоянная дифференцирования
    const double T01; ///< шаг

    /**
     * @brief Конструктор коэффициентов PID-регулятора
     * @param K коэффициент передачи
     * @param T постоянная интегрирования
     * @param Td постоянная дифференцирования
     * @param T0 шаг
     */
    pid_coeffs(double K1, double T1, double Td1, double T01);
};

/**
 * @brief Класс PID-регулятора
 */
class pid
{
private:
    pid_coeffs coeffs;  ///< коэффициенты PID-регулятора   

    double q0;          ///< параметр PID-регулятора
    double q1;          ///< параметр PID-регулятора
    double q2;          ///< параметр PID-регулятора

    double u_prev;      ///< предыдущее значение управляющего воздействия
    double e_prev;      ///< предыдущее значение отклонения
    double e_prev_prev; ///< предпредыдущее значение отклонения

public:
    
    pid(const pid_coeffs& coeffs, double _u, double _e, double __e);

    double process(double e);
};