#include "pid.h"
#include <iostream>
#include <string>

/**
 * @brief Global constants for models
 */
constexpr double TIME_STEP = 0.05;
constexpr double NONLINEAR_COEFF = 0.01;

/**
 * @brief Шаблонная модель динамической системы.
 * Template model of a dynamic system.
 */
template <typename UpdateRule>
class SystemModel {
public:
    double operator()(double input) {
        state = updateRule(state, input);
        return state;
    }

private:
    double state = 0.0;
    UpdateRule updateRule;
};

/**
 * @brief Linear system: y(t+1) = y(t) + T * u
 * Simple thermal model without nonlinearities.
 */
struct LinearUpdate {
    double operator()(double state, double input) const {
        return state + TIME_STEP * input;
    }
};

/**
 * @brief Nonlinear system: y(t+1) = y(t) + T*u + α*u²
 * Accelerates growth for large inputs.
 */
struct NonlinearUpdate {
    double operator()(double state, double input) const {
        return state + TIME_STEP * input + NONLINEAR_COEFF * input * input;
    }
};

using LinearModel    = SystemModel<LinearUpdate>;
using NonlinearModel = SystemModel<NonlinearUpdate>;

/**
 * @brief Universal function for simulating a system with PID.
 */
template <typename Model>
void runSimulation(Model model, int steps, PID& controller, const std::string& name)
{
    std::cout << "=== " << name << " ===\n";

    double measured = 0.0;
    const double setpoint = 1.0;

    for (int i = 0; i < steps; ++i) {
        double control = controller.compute(setpoint, measured);
        measured = model(control);

        std::cout << "Step " << i
                  << " | Setpoint: " << setpoint
                  << " | Control: " << control
                  << " | Output: " << measured << "\n";
    }

    std::cout << name << " simulation finished.\n\n";
}

int main() {
    PID linearPID(1.0, 0.1, 0.05);
    PID nonlinearPID(1.0, 0.1, 0.05);

    const int steps = 50;

    runSimulation(LinearModel{}, steps, linearPID, "Linear Model");
    runSimulation(NonlinearModel{}, steps, nonlinearPID, "Nonlinear Model");

    std::cout << "Simulations completed.\n";
    return 0;
}
