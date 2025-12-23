/**
 * @file pid.h
 * @brief Заголовочный файл для класса дискретного ПИД-регулятора
 * @author Степанюк Илья Сергеевич (ii02720)
 * @date 2025
 * 
 * Определяет класс PIDController, реализующий дискретный ПИД-регулятор
 * с использованием рекуррентного алгоритма вычисления управления.
 */

#ifndef PID_CONTROLLER_H_STEPANIUK
#define PID_CONTROLLER_H_STEPANIUK

#include <vector>

/**
 * @class PIDController
 * @brief Дискретный ПИД-регулятор с рекуррентным алгоритмом
 * 
 * Реализует дискретный пропорционально-интегрально-дифференциальный
 * регулятор для системы автоматического управления тепловым объектом.
 * Использует рекуррентный алгоритм: u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
 * 
 * Разработано для лабораторной работы №3 ОТИС (Степанюк И.С., гр. ИИ-27)
 */
class PIDController {
private:
    double K;          ///< Коэффициент передачи регулятора
    double T;          ///< Постоянная интегрирования (Ти)
    double Td;         ///< Постоянная дифференцирования (Тд)
    double T0;         ///< Период квантования (шаг дискретизации)
    
    double q0;         ///< Коэффициент q0 = K*(1 + Td/T0)
    double q1;         ///< Коэффициент q1 = -K*(1 + 2*Td/T0 - T0/T)
    double q2;         ///< Коэффициент q2 = K*Td/T0
    
    std::vector<double> prev_error;  ///< Буфер ошибок [e(k-1), e(k-2)]
    double prev_output;    ///< Предыдущее управляющее воздействие u(k-1)

public:
    /**
     * @brief Конструктор ПИД-регулятора
     * @param gainK Коэффициент передачи K
     * @param integralT Постоянная интегрирования T
     * @param derivativeTd Постоянная дифференцирования Td
     * @param samplingT0 Период квантования T0
     * @throws std::invalid_argument если T0 <= 0
     */
    PIDController(double gainK, double integralT, double derivativeTd, double samplingT0);
    
    /**
     * @brief Вычисляет управляющее воздействие u(k)
     * @param targetSetpoint Заданное значение w(k)
     * @param measuredValue Измеренное значение y(k)
     * @return Управляющее воздействие u(k)
     */
    double calculate(double targetSetpoint, double measuredValue);
    
    /**
     * @brief Сбрасывает внутреннее состояние регулятора
     * 
     * Обнуляет буфер ошибок и предыдущее управление
     */
    void reset();
    
    /**
     * @brief Возвращает коэффициенты рекуррентного алгоритма
     * @return Вектор коэффициентов [q0, q1, q2]
     */
    std::vector<double> getCoefficients() const;
    
    /**
     * @brief Возвращает параметры регулятора (Степанюк И.С.)
     * @return Вектор параметров [K, T, Td, T0]
     */
    std::vector<double> getParameters() const;
};

#endif // PID_CONTROLLER_H_STEPANIUK
