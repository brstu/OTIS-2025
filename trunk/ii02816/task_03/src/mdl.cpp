/**
 * @file mdl.cpp
 * @brief Implementation of process model methods for thermal object simulation
 * @author Litvinchuk I.M.
 * @date 2025
 */

#include "mdl.h"
#include <stdexcept>
#include <cmath>

/**
 * @brief Constructs a new Process Model object
 * 
 * Initializes the thermal object model with given parameters and starting condition.
 * The model represents a physical system with thermal inertia characteristics.
 * 
 * @param params Vector containing 4 model coefficients:
 *               [a1, a2, b1, b2] where:
 *               - a1: Linear state coefficient
 *               - a2: Nonlinear damping coefficient  
 *               - b1: Linear input gain
 *               - b2: Nonlinear sinusoidal input gain
 * @param initial_value Starting temperature or output value of the system
 * 
 * @throw std::invalid_argument If insufficient parameters provided (less than 4)
 * 
 * @note The model assumes normalized values where 0.0 represents minimum 
 *       and 1.0 represents maximum operational range
 */
ProcessModel::ProcessModel(const std::vector<double>& params, double initial_value) 
    : prev_value(initial_value) {
    
    // Validate input parameters
    if (params.size() < 4) {
        throw std::invalid_argument("Process model requires exactly 4 parameters: "
                                    "linear_coeff, nonlinear_coeff, input_gain, sin_gain");
    }
    
    // Copy validated parameters
    this->params = params;
    
    // Initialize internal state
    this->prev_value = initial_value;
}

/**
 * @brief Computes linear model response
 * 
 * Implements first-order linear difference equation representing 
 * simplified thermal dynamics:
 *   y[k] = a₁·y[k-1] + b₁·u[k]
 * 
 * This model assumes linear relationship between current output,
 * previous output, and current input without nonlinear effects.
 * 
 * @param input Control signal or heat input at current time step
 * @return double Current system output (temperature)
 * 
 * @warning Model may exhibit unrealistic behavior for large inputs
 *          due to lack of saturation effects
 */
double ProcessModel::linearModel(double input) {
    // Linear dynamics calculation
    double output = params[0] * prev_value  // State feedback
                  + params[1] * input;      // Input contribution
    
    // Update internal state for next iteration
    prev_value = output;
    
    return output;
}

/**
 * @brief Computes nonlinear model response with thermal effects
 * 
 * Implements enhanced model capturing nonlinear thermal phenomena:
 *   y[k] = a₁·y[k-1] - a₂·y[k-1]² + b₁·u[k] + b₂·sin(u[k])
 * 
 * The model includes:
 * 1. Quadratic damping term representing heat loss non-linearity
 * 2. Sinusoidal input coupling for periodic excitation effects
 * 
 * @param input Control signal or heat input at current time step
 * @return double Current system output with nonlinear effects
 * 
 * @note The sinusoidal term models alternating heat transfer effects
 *       common in certain thermal systems
 */
double ProcessModel::nonlinearModel(double input) {
    // Calculate base linear response
    double linear_component = params[0] * prev_value
                            + params[2] * input;
    
    // Add nonlinear effects
    double nonlinear_damping = params[1] * prev_value * prev_value;  // Quadratic loss
    double periodic_effect = params[3] * std::sin(input);            // Sinusoidal coupling
    
    // Combine all components
    double output = linear_component 
                  - nonlinear_damping 
                  + periodic_effect;
    
    // Update internal state
    prev_value = output;
    
    return output;
}

/**
 * @brief Resets the model to specified initial condition
 * 
 * Allows re-initialization of the model state without reconstructing
 * the object. Useful for comparing multiple simulation runs or
 * switching between different operating points.
 * 
 * @param value New initial value for the system state
 * 
 * @see ProcessModel::ProcessModel() for constructor initialization
 * 
 * @note Resetting preserves model parameters, only changes state
 */
void ProcessModel::setInitialValue(double value) {
    prev_value = value;
}

/**
 * @brief Retrieves current model parameters
 * 
 * Provides read-only access to the model coefficients for
 * diagnostic or analysis purposes.
 * 
 * @return const std::vector<double>& Reference to model parameters
 * 
 * @warning Modifying returned vector directly may cause undefined behavior
 */

const std::vector<double>& ProcessModel::getParameters() const {
    return params;
}

/**
 * @brief Retrieves current model state
 * 
 * Returns the most recent output value, representing the current
 * state of the simulated thermal system.
 * 
 * @return double Current output value (last computed)
 * 
 * @note This represents y[k-1] at the beginning of next calculation
 */
double ProcessModel::getCurrentState() const {
    return prev_value;
}