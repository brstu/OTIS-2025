#pragma once

struct PIDParameters {
    double Kp = 1.0;           ///< Пропорциональный коэффициент
    double Ki = 0.0;           ///< Интегральный коэффициент
    double Kd = 0.0;           ///< Дифференциальный коэффициент
    double min_output = -1.0;  ///< Минимальное значение выходного сигнала
    double max_output = 1.0;   ///< Максимальное значение выходного сигнала
    double min_integral = -10.0; ///< Минимальное значение интегральной суммы
    double max_integral = 10.0;  ///< Максимальное значение интегральной суммы
    double dt = 1.0;           ///< Время дискретизации (шаг регулирования)
};

/**
 * @class PIDController
 * @brief Класс ПИД-регулятора с ограничением интегральной составляющей
 */
class PIDController {
private:
    PIDParameters params;
    double integral;    ///< Интегральная сумма ошибки
    double prev_error;  ///< Предыдущее значение ошибки для дифференцирования

public:
    /**
     * @brief Конструктор ПИД-регулятора
     * @param kp Пропорциональный коэффициент
     * @param ki Интегральный коэффициент
     * @param kd Дифференциальный коэффициент
     * @param min_out Минимальное значение выходного сигнала (по умолчанию -1.0)
     * @param max_out Максимальное значение выходного сигнала (по умолчанию 1.0)
     * @param min_int Минимальное значение интегральной суммы (по умолчанию -10.0)
     * @param max_int Максимальное значение интегральной суммы (по умолчанию 10.0)
     * @param step_time Время дискретизации (по умолчанию 1.0)
     */
    PIDController(PIDParameters param);
    
    /**
     * @brief Вычисление управляющего воздействия
     * @param setpoint Заданное значение (уставка)
     * @param measured_value Измеренное текущее значение
     * @return Управляющее воздействие (сигнал управления)
     */
    double calculate(double setpoint, double measured_value);
    
    /**
     * @brief Сброс состояния регулятора
     * 
     * Обнуляет интегральную сумму и предыдущую ошибку
     */
    void reset();
    
    /**
     * @brief Установка новых коэффициентов регулятора
     * @param kp Новый пропорциональный коэффициент
     * @param ki Новый интегральный коэффициент
     * @param kd Новый дифференциальный коэффициент
     */
    void setParameters(double kp, double ki, double kd);
    
    /**
     * @brief Установка ограничений выходного сигнала
     * @param min Минимальное значение
     * @param max Максимальное значение
     */
    void setOutputLimits(double min, double max);
    
    /**
     * @brief Установка ограничений интегральной суммы
     * @param min Минимальное значение
     * @param max Максимальное значение
     */
    void setIntegralLimits(double min, double max);
};