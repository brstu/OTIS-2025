#pragma once

/**
 * @class PIDController
 * @brief Класс ПИД-регулятора с ограничением интегральной составляющей
 */
class PIDController {
private:
    double Kp;          ///< Пропорциональный коэффициент
    double Ki;          ///< Интегральный коэффициент
    double Kd;          ///< Дифференциальный коэффициент
    
    double integral;    ///< Интегральная сумма ошибки
    double prev_error;  ///< Предыдущее значение ошибки для дифференцирования
    
    double min_output;  ///< Минимальное значение выходного сигнала
    double max_output;  ///< Максимальное значение выходного сигнала
    
    double min_integral; ///< Минимальное значение интегральной суммы
    double max_integral; ///< Максимальное значение интегральной суммы
    
    double dt;          ///< Время дискретизации (шаг регулирования)

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
    PIDController(double kp, double ki, double kd, 
                  double min_out = -1.0, double max_out = 1.0,
                  double min_int = -10.0, double max_int = 10.0,
                  double step_time = 1.0);
    
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