/**
 * @file pid_controller.h
 * @brief Заголовочный файл для класса PID-регулятора
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

 /**
  * @class PIDController
  * @brief Класс, реализующий ПИД-регулятор
  *
  * Класс реализует алгоритм ПИД-регулятора для управления температурой
  * с ограничением выходного сигнала и защитой от интегрального насыщения
  */
class PIDController {
private:
    double Kp;          ///< Пропорциональный коэффициент
    double Ki;          ///< Интегральный коэффициент  
    double Kd;          ///< Дифференциальный коэффициент
    double setpoint {0};    ///< Заданное значение температуры
    double integral {0};    ///< Интегральная составляющая
    double prev_error {0};  ///< Предыдущая ошибка
    double output_min;  ///< Минимальное значение выходного сигнала
    double output_max;  ///< Максимальное значение выходного сигнала

public:
    /**
     * @brief Конструктор PID-регулятора
     * @param p Пропорциональный коэффициент
     * @param i Интегральный коэффициент
     * @param d Дифференциальный коэффициент
     * @param min Минимальное значение выходного сигнала (по умолчанию 0)
     * @param max Максимальное значение выходного сигнала (по умолчанию 100)
     */
    PIDController(double p, double i, double d, double min = 0, double max = 100);

    /**
     * @brief Вычисляет выходной сигнал ПИД-регулятора
     * @param measured_value Измеренное значение температуры
     * @param dt Временной интервал (шаг) в секундах
     * @return Управляющее воздействие
     */
    double calculate(double measured_value, double dt);

    /**
     * @brief Устанавливает заданное значение температуры
     * @param value Новое заданное значение
     */
    void setSetpoint(double value);

    /**
     * @brief Получает текущее заданное значение
     * @return Заданное значение температуры
     */
    double getSetpoint() const;

    /**
     * @brief Сбрасывает интегральную составляющую и предыдущую ошибку
     */
    void reset();

    /**
     * @brief Устанавливает новые коэффициенты ПИД-регулятора
     * @param p Новый пропорциональный коэффициент
     * @param i Новый интегральный коэффициент
     * @param d Новый дифференциальный коэффициент
     */
    void setParameters(double p, double i, double d);
};

#endif // PID_CONTROLLER_H