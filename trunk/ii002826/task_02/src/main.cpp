#include "models/model_base.h"
#include "models/linear_model.h"
#include "models/nonlinear_model.h"
#include "models/model_factory.h"
#include <iostream>
#include <memory>

int main() {
    const double initial_condition = 0.0;
    const double input_signal = 1.0;
    const int simulation_time = 25;

    // Тестирование линейной модели
    std::cout << "Linear Model Simulation:" << std::endl;
    auto linear_factory = std::make_unique<LinearModelFactory>();
    auto linear_model = linear_factory->createModel();
    linear_model->simulate(initial_condition, input_signal, simulation_time);
    std::cout << std::endl;

    // Тестирование нелинейной модели
    std::cout << "Nonlinear Model Simulation:" << std::endl;
    auto nonlinear_factory = std::make_unique<NonLinearModelFactory>();
    auto nonlinear_model = nonlinear_factory->createModel();
    nonlinear_model->simulate(initial_condition, input_signal, simulation_time);
    std::cout << std::endl;

    return 0;
}