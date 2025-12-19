#ifndef PID_H
#define PID_H

#include <cstddef>

/**
 * @brief Конфигурация ПИД‑регулятора.
 *
 * @note Используется дискретная инкрементная форма:
 *       u(k) - u(k-1) = q0*e(k) + q1*e(k-1) + q2*e(k-2)
 */
struct PIDConfig {
    /**
     * @brief Коэффициент передачи K.
     */
    double K = 1.0;

    /**
     * @brief Постоянная интегрирования T (сек).
     * @note При T -> +inf интегральная часть выключена.
     */
    double T = 1.0;

    /**
     * @brief Постоянная дифференцирования TD (сек).
     * @note При TD = 0 дифференциальная часть выключена.
     */
    double TD = 0.0;

    /**
     * @brief Шаг дискретизации T0 (сек).
     */
    double T0 = 0.1;

    /**
     * @brief Ограничение на выход u (сатурация), |u| <= u_max. 0 — нет.
     */
    double u_max = 0.0;

    /**
     * @brief Включить анти‑windup для интегральной части при насыщении.
     */
    bool anti_windup = true;
};

/**
 * @brief ПИД‑регулятор в инкрементной форме.
 *
 * Реализует
 * u(k) = u(k-1) + Δu,
 * Δu = q0*e(k) + q1*e(k-1) + q2*e(k-2),
 * где:
 * q0 = K*(1 + TD/T0),
 * q1 = -K*(1 + 2*TD/T0 - T0/T),
 * q2 = K*(TD/T0).
 */
class PID {
public:
    /**
     * @brief Создать ПИД по конфигурации.
     */
    explicit PID(const PIDConfig& cfg);

    /**
     * @brief Сбросить внутреннее состояние.
     * @param u0 Начальное значение u(-1).
     * @param e_1 Начальное значение e(-1).
     * @param e_2 Начальное значение e(-2).
     */
    void reset(double u0 = 0.0, double e_1 = 0.0, double e_2 = 0.0);

    /**
     * @brief Выполнить шаг регулятора.
     * @param e_k Текущее значение ошибки e(k).
     * @return Текущее значение управляющего воздействия u(k).
     */
    double step(double e_k);

    /**
     * @brief Получить текущее значение u(k).
     */
    double u() const { return u_k_; }

    /**
     * @brief Получить коэффициенты q0, q1, q2.
     */
    void get_q(double& q0, double& q1, double& q2) const;

private:
    PIDConfig cfg_;
    double q0_{0.0};
    double q1_{0.0};
    double q2_{0.0};
    double u_k_{0.0};
    double e_k_{0.0};
    double e_k1_{0.0};
    double e_k2_{0.0};

    void compute_q();
    double saturate(double v) const;
};

#endif
