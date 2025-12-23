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
pid_coeffs::pid_coeffs(double K1, double T1, double Td1, double T01)
        : K1(K1), T1(T1), Td1(Td1), T01(T01) {}


pid::pid(const pid_coeffs& coeffs, double _u, double _e, double __e)
    : coeffs(coeffs),
      q0(coeffs.K1 * (1 + coeffs.Td1 / coeffs.T01)),
      q1(-coeffs.K1 * (1 + 2 * coeffs.Td1 / coeffs.T01 - coeffs.T01 / coeffs.T1)),
      q2(coeffs.K1 * coeffs.Td1 / coeffs.T01),
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
