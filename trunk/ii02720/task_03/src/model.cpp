/**
 * @file process_model.cpp
 * @brief Реализация методов модели объекта управления
 * @author Степанюк Илья Сергеевич (ii02720)
 * @date 2025
 * 
 * Данный модуль содержит реализацию класса ProcessModel,
 * который моделирует тепловой объект управления для
 * лабораторной работы №3 по дисциплине ОТИС.
 */

#include "model.h"
#include <stdexcept>

// Минимальное количество параметров для инициализации модели
const int MIN_PARAMS_COUNT_STEPANIUK = 4;

ProcessModel::ProcessModel(const std::vector<double>& modelParameters, double startValue) {
    if (modelParameters.size() < MIN_PARAMS_COUNT_STEPANIUK) {
        throw std::invalid_argument("Недостаточно параметров модели (требуется минимум 4)");
    }
    this->params = modelParameters;
    this->prev_value = startValue;
}

double ProcessModel::linearModel(double inputSignal) {
    // Линейная модель теплового объекта: y(k) = a*y(k-1) + b*u(k)
    double outputValue = params[0] * prev_value + params[1] * inputSignal;
    prev_value = outputValue;
    return outputValue;
}

double ProcessModel::nonlinearModel(double inputSignal) {
    // Нелинейная модель с учетом квадратичной составляющей и синуса
    // y(k) = a*y(k-1) - b*y(k-1)^2 + c*u(k) + d*sin(u(k))
    double outputValue = params[0] * prev_value - params[1] * prev_value * prev_value 
                   + params[2] * inputSignal + params[3] * std::sin(inputSignal);
    prev_value = outputValue;
    return outputValue;
}

void ProcessModel::setInitialValue(double initialValue) {
    prev_value = initialValue;
}

// Метод для получения текущего значения выхода модели (добавлено Степанюк И.С.)
double ProcessModel::getCurrentValue() const {
    return prev_value;
}
