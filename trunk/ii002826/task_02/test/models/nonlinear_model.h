#ifndef NONLINEAR_MODEL_H
#define NONLINEAR_MODEL_H

#include "model_base.h"
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

class NonLinearModel : public ISimulatedModel {
public:
    NonLinearModel(double coefficient_a, double coefficient_b,
        double coefficient_c, double coefficient_d)
        : coefficient_a_(coefficient_a), coefficient_b_(coefficient_b),
        coefficient_c_(coefficient_c), coefficient_d_(coefficient_d) {
    }

    ~NonLinearModel() override = default;

    void simulate(double initial_value, double input, int time_steps) const override {
        double current_value = initial_value;
        double previous_value = initial_value;
        double previous_input = input;
        double current_input = input;

        for (int step = 0; step <= time_steps; step++) {
            std::cout << step << " " << current_value << std::endl;

            double next_value = coefficient_a_ * current_value
                - coefficient_b_ * previous_value * previous_value
                + coefficient_c_ * current_input
                + coefficient_d_ * std::sin(previous_input);

            previous_value = current_value;
            previous_input = current_input;
            current_input += input_step_;
            current_value = next_value;
        }
    }

    // Метод для тестирования - возвращает все значения симуляции
    std::vector<double> simulateWithResults(double initial_value, double input, int time_steps) const {
        std::vector<double> results;
        double current_value = initial_value;
        double previous_value = initial_value;
        double previous_input = input;
        double current_input = input;

        for (int step = 0; step <= time_steps; step++) {
            results.push_back(current_value);

            double next_value = coefficient_a_ * current_value
                - coefficient_b_ * previous_value * previous_value
                + coefficient_c_ * current_input
                + coefficient_d_ * std::sin(previous_input);

            previous_value = current_value;
            previous_input = current_input;
            current_input += input_step_;
            current_value = next_value;
        }
        return results;
    }

    double getCoefficientA() const { return coefficient_a_; }
    double getCoefficientB() const { return coefficient_b_; }
    double getCoefficientC() const { return coefficient_c_; }
    double getCoefficientD() const { return coefficient_d_; }

private:
    const double coefficient_a_;
    const double coefficient_b_;
    const double coefficient_c_;
    const double coefficient_d_;
    const double input_step_ = 0.5;
};

#endif