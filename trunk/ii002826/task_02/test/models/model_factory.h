#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include "linear_model.h"
#include "nonlinear_model.h"

class LinearModelFactory : public IModelFactory {
public:
    ~LinearModelFactory() override = default;

    std::unique_ptr<ISimulatedModel> createModel() const override {
        return std::make_unique<LinearModel>(linear_coefficient_a, linear_coefficient_b);
    }

    double getCoefficientA() const { return linear_coefficient_a; }
    double getCoefficientB() const { return linear_coefficient_b; }

private:
    const double linear_coefficient_a = 0.5;
    const double linear_coefficient_b = 0.5;
};

class NonLinearModelFactory : public IModelFactory {
public:
    ~NonLinearModelFactory() override = default;

    std::unique_ptr<ISimulatedModel> createModel() const override {
        return std::make_unique<NonLinearModel>(nonlinear_coefficient_a, nonlinear_coefficient_b,
            nonlinear_coefficient_c, nonlinear_coefficient_d);
    }

    double getCoefficientA() const { return nonlinear_coefficient_a; }
    double getCoefficientB() const { return nonlinear_coefficient_b; }
    double getCoefficientC() const { return nonlinear_coefficient_c; }
    double getCoefficientD() const { return nonlinear_coefficient_d; }

private:
    const double nonlinear_coefficient_a = 0.5;
    const double nonlinear_coefficient_b = 0.5;
    const double nonlinear_coefficient_c = 0.5;
    const double nonlinear_coefficient_d = 0.5;
};

#endif