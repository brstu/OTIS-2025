#include "module.h"
#include <cmath>

void calculate_linear_model(
    int total_steps,
    double coefficient_a,
    double coefficient_b,
    const std::vector<double>& input_signal,
    std::vector<double>& linear_result
)
{
    for (int current_step = 0; current_step < total_steps; ++current_step)
    {
        int next_index = current_step + 1;
        double current_value = linear_result[current_step];
        double input_value = input_signal[current_step];
        
        linear_result[next_index] = coefficient_a * current_value + coefficient_b * input_value;
    }
}

void calculate_nonlinear_model(
    int iteration_count,
    double alpha,
    double beta,
    double gamma,
    double delta,
    const std::vector<double>& control_input,
    std::vector<double>& nonlinear_result
)
{
    for (int step_index = 1; step_index < iteration_count; ++step_index)
    {
        bool valid_previous_index = step_index - 1 >= 0;
        bool valid_current_index = step_index < static_cast<int>(nonlinear_result.size());
        
        if (valid_previous_index && valid_current_index)
        {
            double first_component = alpha * nonlinear_result[step_index];
            
            double second_component = beta * nonlinear_result[step_index - 1];
            second_component = second_component * nonlinear_result[step_index - 1];
            
            double third_component = gamma * control_input[step_index];
            
            double fourth_component = delta * std::sin(control_input[step_index - 1]);
            
            int target_index = step_index + 1;
            
            nonlinear_result[target_index] = first_component - second_component + third_component + fourth_component;
        }
    }
}