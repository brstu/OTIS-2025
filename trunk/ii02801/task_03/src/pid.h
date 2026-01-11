/**
 * @file pid.h
 * @brief Заголовочный файл для класса ПИД-регулятора
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <vector>

/**
 * @class PIDController
 * @brief Класс, реализующий дискретный ПИД-регулятор
 * 
 * Данный класс реализует дискретный ПИД-регулятор с использованием 
 * рекуррентного алгоритма для вычисления управляющего воздействия.
 */
class PIDController {
private:
    double K;          ///< Коэффициент передачи
    double T;          ///< Постоянная интегрирования
    double Td;         ///< Постоянная дифференцирования
    double T0;         ///< Время квантования
    
    double q0;         ///< Коэффициент q0
    double q1;         ///< Коэффициент q1  
    double q2;         ///< Коэффициент q2
    
    std::vector<double> prev_error;  ///< Предыдущие ошибки e(k-1) и e(k-2)
    double prev_output;    ///< Предыдущее выходное значение u(k-1)

public:
    /**
     * @brief Конструктор ПИД-регулятора
     * @param K Коэффициент передачи
     * @param T Постоянная интегрирования
     * @param Td Постоянная дифференцирования
     * @param T0 Время квантования
     */
    PIDController(double K, double T, double Td, double T0);
    
    /**
     * @brief Вычисляет управляющее воздействие
     * @param setpoint Заданное значение
     * @param current_value Текущее значение процесса
     * @return Управляющее воздействие
     */
    double calculate(double setpoint, double current_value);
    
    /**
     * @brief Сбрасывает состояние регулятора
     */
    void reset();
    
    /**
     * @brief Возвращает коэффициенты регулятора
     * @return Вектор коэффициентов [q0, q1, q2]
     */
    std::vector<double> getCoefficients() const;
};

#endif