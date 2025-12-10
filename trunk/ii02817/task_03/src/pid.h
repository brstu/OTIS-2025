/**
 * @file pid.h
 * @brief Дискретный ПИД-регулятор
 *
 * Реализация дискретного ПИД-регулятора по рекуррентным формулам
 */

#ifndef PID_H
#define PID_H
#include <vector>
/**
 * @class PIDController
 * @brief Дискретный ПИД-регулятор
 */
class PIDController
{
private:
    double K = 1.0;  ///< Коэффициент усиления
    double Ti = 1.0; ///< Постоянная интегрирования
    double Td = 0.0; ///< Постоянная дифференцирования
    double T0 = 1.0; ///< Шаг квантования

    double q0 = 1.0; ///< Коэффициент q0
    double q1 = 0.0; ///< Коэффициент q1
    double q2 = 0.0; ///< Коэффициент q2

    double u_prev = 0.0;  ///< Предыдущее управляющее воздействие
    double e_prev1 = 0.0; ///< Ошибка на шаге k-1
    double e_prev2 = 0.0; ///< Ошибка на шаге k-2
    double u_max = 100.0; ///< Максимальное значение управления

public:
    /**
     * @brief Конструктор по умолчанию
     */
    PIDController() = default;

    /**
     * @brief Параметризованный конструктор
     * @param K Коэффициент усиления
     * @param Ti Постоянная интегрирования
     * @param Td Постоянная дифференцирования
     * @param T0 Шаг квантования
     */
    PIDController(double K, double Ti, double Td, double T0);

    /**
     * @brief Установка параметров ПИД-регулятора
     * @param K Коэффициент усиления
     * @param Ti Постоянная интегрирования
     * @param Td Постоянная дифференцирования
     * @param T0 Шаг квантования
     */
    void setParameters(double K, double Ti, double Td, double T0);

    /**
     * @brief Установка ограничений управления
     * @param u_min Минимальное значение управления
     * @param u_max Максимальное значение управления
     */
    void setLimits(double u_max);

    /**
     * @brief Сброс состояния регулятора
     */
    void reset();

    /**
     * @brief Вычисление управляющего воздействия
     * @param e Текущая ошибка (задание - измерение)
     * @return Управляющее воздействие
     */
    double calculate(double e);

    /**
     * @brief Получение коэффициентов регулятора
     * @return Вектор коэффициентов [q0, q1, q2]
     */
    std::vector<double> getCoefficients() const;
};

#endif // PID_H