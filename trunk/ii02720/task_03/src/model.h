/**
 * @file model.h
 * @brief Заголовочный файл для модели объекта управления
 * @author Степанюк Илья Сергеевич (ii02720)
 * @date 2025
 * 
 * Модуль определяет класс ProcessModel для моделирования
 * теплового объекта управления в системе с ПИД-регулятором.
 */

#ifndef PROCESS_MODEL_H_STEPANIUK
#define PROCESS_MODEL_H_STEPANIUK

#include <vector>
#include <cmath>

/**
 * @class ProcessModel
 * @brief Класс для моделирования теплового объекта управления
 * 
 * Реализует математическую модель объекта управления теплового класса,
 * которая может функционировать как в линейном, так и в нелинейном режиме.
 * Разработано для лабораторной работы №3 ОТИС (Степанюк И.С., группа ИИ-27).
 */
class ProcessModel {
private:
    std::vector<double> params;  ///< Вектор параметров модели [a, b, c, d]
    double prev_value;           ///< Предыдущее значение выхода y(k-1)
    
public:
    /**
     * @brief Конструктор модели теплового объекта
     * @param modelParameters Вектор параметров модели (минимум 4 элемента)
     * @param startValue Начальное значение выходной переменной
     * @throws std::invalid_argument если параметров меньше 4
     */
    ProcessModel(const std::vector<double>& modelParameters, double startValue);
    
    /**
     * @brief Вычисляет выход линейной модели объекта
     * @param inputSignal Входное управляющее воздействие u(k)
     * @return Выходное значение y(k) = a*y(k-1) + b*u(k)
     */
    double linearModel(double inputSignal);
    
    /**
     * @brief Вычисляет выход нелинейной модели объекта
     * @param inputSignal Входное управляющее воздействие u(k)
     * @return Выходное значение с нелинейными составляющими
     */
    double nonlinearModel(double inputSignal);
    
    /**
     * @brief Устанавливает начальное значение выхода модели
     * @param initialValue Новое начальное значение y(0)
     */
    void setInitialValue(double initialValue);
    
    /**
     * @brief Возвращает текущее значение выхода модели
     * @return Текущее значение y(k-1)
     * @note Добавлено Степанюком И.С. для отладки
     */
    double getCurrentValue() const;
};

#endif // PROCESS_MODEL_H_STEPANIUK
