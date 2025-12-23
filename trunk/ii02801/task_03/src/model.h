/**
 * @file model.h
 * @brief Заголовочный файл для модели объекта управления
 */

#ifndef PROCESS_MODEL_H
#define PROCESS_MODEL_H

#include <vector>
#include <cmath>

/**
 * @class ProcessModel
 * @brief Класс, моделирующий объект управления
 * 
 * Модель объекта управления, которая может работать как в линейном,
 * так и в нелинейном режиме.
 */
class ProcessModel {
private:
    std::vector<double> params;  ///< Параметры модели
    double prev_value;           ///< Предыдущее значение выхода
    
public:
    /**
     * @brief Конструктор модели процесса
     * @param params Вектор параметров модели
     * @param initial_value Начальное значение
     */
    ProcessModel(const std::vector<double>& params, double initial_value);
    
    /**
     * @brief Линейная модель объекта
     * @param input Входное воздействие
     * @return Выходное значение
     */
    double linearModel(double input);
    
    /**
     * @brief Нелинейная модель объекта  
     * @param input Входное воздействие
     * @return Выходное значение
     */
    double nonlinearModel(double input);
    
    /**
     * @brief Устанавливает начальное значение
     * @param value Начальное значение
     */
    void setInitialValue(double value);
};

#endif