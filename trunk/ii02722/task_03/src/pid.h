#ifndef PID_H
#define PID_H

/**
 * @brief Класс PID-регулятора.
 *
 * Реализует дискретный PID-контроллер с простым накоплением интеграла
 * и расчетом производной по разности ошибок.
 */
class PID {
public:
    /**
     * @brief Конструктор PID.
     * @param kp Пропорциональный коэффициент.
     * @param ki Интегральный коэффициент.
     * @param kd Дифференциальный коэффициент.
     */
    PID(double kp, double ki, double kd);

    /**
     * @brief Установить новые коэффициенты PID.
     * @param kp Пропорциональный коэффициент.
     * @param ki Интегральный коэффициент.
     * @param kd Дифференциальный коэффициент.
     */
    void setCoefficients(double kp, double ki, double kd);

    /**
     * @brief Вычислить управляющее воздействие.
     *
     * @param setpoint Желаемое значение (задание).
     * @param measurement Текущее измеренное значение.
     * @param dt Шаг дискретизации (секунды).
     * @return Управляющее воздействие u.
     */
    double compute(double setpoint, double measurement, double dt);

    /**
     * @brief Сбросить внутреннее состояние регулятора.
     *
     * Обнуляет интегральную составляющую и предыдущую ошибку.
     */
    void reset();

private:
    double kp;          ///< Пропорциональный коэффициент.
    double ki;          ///< Интегральный коэффициент.
    double kd;          ///< Дифференциальный коэффициент.
    double prev_error;  ///< Ошибка на предыдущем шаге.
    double integral;    ///< Накопленная интегральная ошибка.
};

#endif // PID_H
