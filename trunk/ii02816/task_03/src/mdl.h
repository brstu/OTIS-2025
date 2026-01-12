// process_model.h
#ifndef PROCESS_MODEL_H
#define PROCESS_MODEL_H

#include <vector>

class ProcessModel {
public:
    /**
     * @brief Constructs a new Process Model object
     * @param params Vector containing 4 model coefficients:
     *               [a1, a2, b1, b2]
     * @param initial_value Starting output value of the system
     */
    ProcessModel(const std::vector<double>& params, double initial_value);
    
    /**
     * @brief Sets new model parameters
     * @param new_params Vector of 4 coefficients
     * @throw std::invalid_argument If insufficient parameters provided
     */
    void setParameters(const std::vector<double>& new_params);
    
    /**
     * @brief Retrieves model parameters
     * @return const std::vector<double>& Reference to model parameters
     */
    const std::vector<double>& getParameters() const;
    
    /**
     * @brief Computes linear model response
     * @param input Control signal at current time step
     * @return double Current system output
     */
    double linearModel(double input);
    
    /**
     * @brief Computes nonlinear model response
     * @param input Control signal at current time step  
     * @return double Current system output with nonlinear effects
     */
    double nonlinearModel(double input);
    
    /**
     * @brief Resets the model to specified initial condition
     * @param value New initial value for the system state
     */
    void setInitialValue(double value);
    
    /**
     * @brief Retrieves current model state (last computed output y[k])
     * @return double Current output value
     */
    double getCurrentState() const;
    
    /**
     * @brief Retrieves previous model state (y[k-1] before last update)
     * @return double Previous output value
     */
    double getPreviousState() const;
    
private:
    std::vector<double> params;    // [a1, a2, b1, b2]
    double current_value;          // y[k] - текущее значение
    double prev_value;             // y[k-1] - предыдущее значение
};

#endif