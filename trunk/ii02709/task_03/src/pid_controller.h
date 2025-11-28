#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

/**
 * @brief Дискретный ПИД-регулятор (инкрементальная форма)
 */
class PIDController {
    double K{};
    double Ti{1e9};   ///< По умолчанию интеграл отключён
    double Td{0.0};
    double dt{0.1};

    double q0{}, q1{}, q2{};
    double u_prev{};
    double e_prev1{};
    double e_prev2{};

public:
    /**
     * @brief Конструктор
     * @param k  Коэффициент усиления
     * @param ti Постоянная интегрирования (Ti → ∞ отключает I)
     * @param td Постоянная дифференцирования
     * @param dtt Шаг дискретизации
     */
    PIDController(double k, double ti, double td, double dtt);

    /** @brief Вычисляет управление u(k) */
    double compute(double e);

    /** @brief Сбрасывает состояние */
    void reset();
};

#endif // PID_CONTROLLER_H