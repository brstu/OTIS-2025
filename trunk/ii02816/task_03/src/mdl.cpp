/**
 * @file process_model.cpp
 * @brief Реализация методов модели объекта управления
 */

#include "mdl.h"
#include <stdexcept>

ProcessModel::ProcessModel(const std::vector<double>& params, double initial_value) {
    if (params.size() < 4) {
        throw std::invalid_argument("Недостаточно параметров модели");
    }
    this->params = params;
    this->prev_value = initial_value;
}

double ProcessModel::linearModel(double input) {
    
    double output = params[0] * prev_value + params[1] * input;
    prev_value = output;
    return output;
}

double ProcessModel::nonlinearModel(double input) {
    
    double output = params[0] * prev_value - params[1] * prev_value * prev_value 
                   + params[2] * input + params[3] * std::sin(input);
    prev_value = output;
    return output;
}

void ProcessModel::setInitialValue(double value) {
    prev_value = value;
}