/**
 * @file pid.h
 * @brief Дискретный PID-регулятор (приращённая форма)
 */

#pragma once

/**
 * @struct PIDParams
 * @brief Параметры ПИД-регулятора
 */
struct PIDParams {
    double K;   ///< коэффициент передачи
    double T;   ///< постоянная интегрирования
    double Td;  ///< постоянная дифференцирования
    double T0;  ///< шаг дискретизации
};

/**
 * @class PID
 * @brief Дискретный ПИД-регулятор в приращённой форме:
 *
 * u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
 */
class PID {
public:
    explicit PID(const PIDParams& p);

    /**
     * @brief Вычислить управляющее воздействие
     * @param e текущее отклонение e(k)
     * @return u(k)
     */
    double update(double e);

    /** @brief Сброс внутреннего состояния */
    void reset();

private:
    PIDParams p_;
    double q0_{ 0.0 };
    double q1_{ 0.0 };
    double q2_{ 0.0 };
    double u_prev_{0.0};
    double e_prev_{0.0};
    double e_prev2_{0.0};
};
