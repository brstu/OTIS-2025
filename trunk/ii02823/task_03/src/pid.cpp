#include "pid.h"

/**
 * @brief Конструктор коэффициентов PID-регулятора
 * 
 * Инициализирует структуру коэффициентов PID-регулятора.
 * 
 * @param K коэффициент передачи
 * @param T постоянная интегрирования
 * @param Td постоянная дифференцирования
 * @param T0 шаг
 */
pid_coeffs::pid_coeffs(double K, double T, double Td, double T0)
        : K(K), T(T), Td(Td), T0(T0) {}

/**
 * @brief Конструктор PID-регулятора
 * 
 * Инициализирует регулятор с заданными коэффициентами и начальными условиями.
 * 
 * @param coeffs структура коэффициентов
 * @param _u начальное значение управляющего воздействия
 * @param _e предыдущее значение отклонения
 * @param __e предпредыдущее значение отклонения
 */
pid::pid(const pid_coeffs& coeffs, double _u, double _e, double __e)
    : coeffs(coeffs),
      q0(coeffs.K * (1 + coeffs.Td / coeffs.T0)),
      q1(-coeffs.K * (1 + 2 * coeffs.Td / coeffs.T0 - coeffs.T0 / coeffs.T)),
      q2(coeffs.K * coeffs.Td / coeffs.T0),
      u_prev(_u),
      e_prev(_e),
      e_prev_prev(__e)
      {

      }

/**
 * @brief Выполнить шаг PID-регулятора
 * 
 * Вычисляет новое управляющее воздействие на основе текущей ошибки.
 * 
 * @param _e текущее значение отклонения
 * @return новое управляющее воздействие
 */
double pid::process(double e)
{
    double _u = q0 * e + q1 * e_prev + q2 * e_prev_prev;
    double u = u_prev + _u;

    u_prev = u;
    e_prev_prev = e_prev;
    e_prev = e;

    return u;
}
