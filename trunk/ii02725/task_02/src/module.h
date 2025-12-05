#ifndef MODULE_H
#define MODULE_H

#include <vector>

const int MAXIMUM_STEPS = 101;

void calculate_linear_model(
    int total_steps,
    double coefficient_a,
    double coefficient_b,
    const std::vector<double>& input_signal,
    std::vector<double>& linear_result
);

void calculate_nonlinear_model(
    int iteration_count,
    double alpha,
    double beta,
    double gamma,
    double delta,
    const std::vector<double>& control_input,
    std::vector<double>& nonlinear_result
);

#endif