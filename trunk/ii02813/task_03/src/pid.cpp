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
        : K01(K01), T01(T01), Td01(Td01), T001(T001) {}

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
      q001(coeffs.K01 * (1 + coeffs.Td01 / coeffs.T001)),
      q101(-coeffs.K01 * (1 + 2 * coeffs.Td01 / coeffs.T001 - coeffs.T001 / coeffs.T01)),
      q201(coeffs.K01 * coeffs.Td01 / coeffs.T001),
      u01_prev(_u01),
      e01_prev(_e01),
      e01_prev_prev(__e01)
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
    double _u01 = q001 * e01 + q101 * e01_prev + q201 * e01_prev_prev;
    double u01 = u01_prev + _u01;

    u01_prev = u01;
    e01_prev_prev = e01_prev;
    e01_prev = e01;

    return u01;
}
