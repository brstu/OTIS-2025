#ifndef LINEAR_MODEL_H
#define LINEAR_MODEL_H

#include "model_base.h"
#include <iostream>
#include <memory>
#include <vector>

class LinearModel : public ISimulatedModel {
public:
    LinearModel(double coefficient_a, double coefficient_b)
        : coefficient_a_(coefficient_a), coefficient_b_(coefficient_b) {
    }

    ~LinearModel() override = default;

    void simulate(double initial_value, double input, int time_steps) const override {
        double current_value = initial_value;

        for (int step = 0; step <= time_steps; step++) {
            std::cout << step << " " << current_value << std::endl;
            current_value = coefficient_a_ * current_value + coefficient_b_ * input;
        }
    }

    // Метод для тестирования - возвращает все значения симуляции
    std::vector<double> simulateWithResults(double initial_value, double input, int time_steps) const {
        std::vector<double> results;
        double current_value = initial_value;

        for (int step = 0; step <= time_steps; step++) {
            results.push_back(current_value);
            current_value = coefficient_a_ * current_value + coefficient_b_ * input;
        }
        return results;
    }

    double getCoefficientA() const { return coefficient_a_; }
    double getCoefficientB() const { return coefficient_b_; }

private:
    const double coefficient_a_;
    const double coefficient_b_;
};

#endif