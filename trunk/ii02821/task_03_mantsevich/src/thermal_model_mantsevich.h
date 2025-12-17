#ifndef THERMAL_MODEL_MANTSEVICH_H
#define THERMAL_MODEL_MANTSEVICH_H

/**
 * @class ThermalModelMantsevich
 * @brief Simple dynamic model for simulation purposes
 * @author Mantsevich R.S. II-28
 *
 * The ThermalModelMantsevich class represents a thermal system whose state 
 * is described by the temperature variable. The temperature can be initialized 
 * and updated via the provided methods.
 */
class ThermalModelMantsevich {
private:
    /**
     * @brief Current state of the model
     *
     * Represents the temperature output of the thermal model
     */
    double temperature{0.0};  ///< in-class initialization

public:
    /**
     * @brief Construct the model with an initial temperature
     * @param initial_temp Initial temperature value (default 0.0)
     */
    explicit ThermalModelMantsevich(double initial_temp = 0.0) noexcept;

    /**
     * @brief Returns the current temperature of the model
     *
     * This method provides read-only access to the current temperature value
     *
     * @return The current temperature value
     */
    double getTemperature() const noexcept;
    
    /**
     * @brief Updates the temperature of the model based on heat input and time step
     *
     * This method updates the internal temperature using the provided heat input signal
     * and the time step. The specific update rule is defined in the implementation
     *
     * @param heat_input Heat input signal to the model, representing the external influence or control input
     * @param dt Time step for the update, representing the elapsed time since the last update (must be positive)
     * @return The updated temperature value after applying the heat input and time step
     */
    double update(double heat_input, double dt) noexcept;
};

#endif // THERMAL_MODEL_MANTSEVICH_H