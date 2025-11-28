/**
 * @file pid_controller.h
 * @brief Дискретный ПИД-регулятор в инкрементальной форме
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PIDController {
private:
    double K;   ///< Коэффициент передачи (пропорциональная часть)
    double Ti;  ///< Постоянная интегрирования
    double Td;  ///< Постоянная дифференцирования
    double dt;  ///< Шаг дискретизации

    double q0, q1, q2; ///< Коэффициенты рекуррентной формы

    double u_prev;    ///< Предыдущее значение управления
    double e_prev1;   ///< e(k-1)
    double e_prev2;   ///< e(k-2)

public:
    /**
     * @brief Конструктор
     * @param k  Коэффициент K
     * @param ti Постоянная интегрирования Ti (большое значение → отключает I)
     * @param td Постоянная дифференцирования Td
     * @param dtt Шаг дискретизации
     */
    PIDController(double k, double ti, double td, double dtt);

    /**
     * @brief Вычисление управляющего воздействия
     * @param e Текущая ошибка e(k) = w - y
     * @return Текущее управление u(k)
     */
    double compute(double e);

    /// @brief Сброс внутреннего состояния регулятора
    void reset();
};

#endif // PID_CONTROLLER_H