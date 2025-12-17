#pragma once

/**
 * @brief Структура коэффициентов PID-регулятора
 */
struct pid_coeffs
{
    const double K;  ///< коэффициент передачи
    const double T;  ///< постоянная интегрирования
    const double Td; ///< постоянная дифференцирования
    const double T0; ///< шаг

    /**
     * @brief Конструктор коэффициентов PID-регулятора
     * @param K коэффициент передачи
     * @param T постоянная интегрирования
     * @param Td постоянная дифференцирования
     * @param T0 шаг
     */
    pid_coeffs(double K, double T, double Td, double T0);
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
    /**
     * @brief Конструктор PID-регулятора
     * @param coeffs структура коэффициентов
     * @param _u начальное значение управляющего воздействия
     * @param _e предыдущее значение отклонения
     * @param __e предпредыдущее значение отклонения
     */
    pid(const pid_coeffs& coeffs, double _u, double _e, double __e);

    /**
     * @brief Выполнить шаг PID-регулятора
     * @param e текущее значение отклонения
     * @return новое управляющее воздействие
     */
    double process(double e);
};