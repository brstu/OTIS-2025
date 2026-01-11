/**
 * @file process_model.h
 * @brief Заголовочный файл для класса динамической системы
 */

#ifndef DYNAMIC_SYSTEM_H
#define DYNAMIC_SYSTEM_H

#include <vector>
#include <cmath>

/**
 * @class DynamicSystem
 * @brief Класс, описывающий поведение динамической системы
 * 
 * Моделирует объект управления, способный функционировать в линейном
 * и нелинейном режимах с различными типами динамических характеристик.
 */
class DynamicSystem {
private:
    std::vector<double> system_coefficients;  ///< Коэффициенты математической модели
    double internal_state;                     ///< Внутреннее состояние системы
    
public:
    /**
     * @brief Конструктор динамической системы
     * @param system_coefficients Массив коэффициентов математической модели
     * @param initial_state Начальное состояние системы
     */
    DynamicSystem(const std::vector<double>& system_coefficients, double initial_state);
    
    /**
     * @brief Линейная аппроксимация динамики системы
     * @param control_input Управляющее воздействие на текущем шаге
     * @return Новое состояние системы
     */
    double evaluateLinear(double control_input);
    
    /**
     * @brief Нелинейная модель динамики системы
     * @param control_input Управляющее воздействие на текущем шаге
     * @return Новое состояние системы с учетом нелинейностей
     */
    double evaluateNonlinear(double control_input);
    
    /**
     * @brief Устанавливает начальное состояние системы
     * @param initial_value Значение начального состояния
     */
    void initializeState(double initial_value);
};

#endif