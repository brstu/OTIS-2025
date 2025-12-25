#pragma once

/**
 * @brief Структура коэффициентов PID-регулятора
 */
struct pid_coeffs
{
    const double K01;  ///< коэффициент передачи
    const double T01;  ///< постоянная интегрирования
    const double Td01; ///< постоянная дифференцирования
    const double T001; ///< шаг

    /**
     * @brief Конструктор коэффициентов PID-регулятора
     * @param K01 коэффициент передачи
     * @param T01 постоянная интегрирования
     * @param Td01 постоянная дифференцирования
     * @param T001 шаг
     */
    pid_coeffs(double K01, double T01, double Td01, double T001);
};

/**
 * @brief Класс PID-регулятора
 */
class pid
{
private:
    pid_coeffs coeffs;  ///< коэффициенты PID-регулятора   

    double q001;          ///< параметр PID-регулятора
    double q101;          ///< параметр PID-регулятора
    double q201;          ///< параметр PID-регулятора

    double u01_prev;      ///< предыдущее значение управляющего воздействия
    double e01_prev;      ///< предыдущее значение отклонения
    double e01_prev_prev; ///< предпредыдущее значение отклонения

public:
    /**
     * @brief Конструктор PID-регулятора
     * @param coeffs структура коэффициентов
     * @param _u01 начальное значение управляющего воздействия
     * @param _e01 предыдущее значение отклонения
     * @param __e01 предпредыдущее значение отклонения
     */
    pid(const pid_coeffs& coeffs, double _u01, double _e01, double __e01);

    /**
     * @brief Выполнить шаг PID-регулятора
     * @param e01 текущее значение отклонения
     * @return новое управляющее воздействие
     */
    double process(double e01);
};