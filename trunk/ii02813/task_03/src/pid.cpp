#include "pid.h"

/**
 * @brief Конструктор коэффициентов PID-регулятора
 * 
 * Инициализирует структуру коэффициентов PID-регулятора.
 * 
 * @param K01 коэффициент передачи
 * @param T01 постоянная интегрирования
 * @param Td01 постоянная дифференцирования
 * @param T001 шаг
 */
pid_coeffs::pid_coeffs(double K01, double T01, double Td01, double T001)
        : K(K01), T(T01), Td(Td01), T0(T001) {}

/**
 * @brief Конструктор PID-регулятора
 * 
 * Инициализирует регулятор с заданными коэффициентами и начальными условиями.
 * 
 * @param coeffs структура коэффициентов
 * @param _u01 начальное значение управляющего воздействия
 * @param _e01 предыдущее значение отклонения
 * @param __e01 предпредыдущее значение отклонения
 */
pid::pid(const pid_coeffs& coeffs, double _u01, double _e01, double __e01)
    : coeffs(coeffs),
      q0(coeffs.K * (1 + coeffs.Td / coeffs.T0)),
      q1(-coeffs.K * (1 + 2 * coeffs.Td / coeffs.T0 - coeffs.T0 / coeffs.T)),
      q2(coeffs.K * coeffs.Td / coeffs.T0),
      u_prev(_u01),
      e_prev(_e01),
      e_prev_prev(__e01)
      {

      }

/**
 * @brief Выполнить шаг PID-регулятора
 * 
 * Вычисляет новое управляющее воздействие на основе текущей ошибки.
 * 
 * @param _e01 текущее значение отклонения
 * @return новое управляющее воздействие
 */
double pid::process(double e01)
{
    double _u01 = q0 * e01 + q1 * e_prev + q2 * e_prev_prev;
    double u01 = u_prev + _u01;

    u_prev = u01;
    e_prev_prev = e_prev;
    e_prev = e01;

    return u01;
}
