/**
 * @file model_ruslan.cpp
 * @brief Implementation of dynamic model class
 * @author Mantsevich R.S.
 * @date 2025
 */

#include "thermal_model_mantsevich.h"

/**
 * @brief Constructor for dynamic model
 * @param initial_temp Initial temperature value
 */
ThermalModelMantsevich::ThermalModelMantsevich(double initial_temp) noexcept
    : temperature(initial_temp) {}

/**
 * @brief Get current temperature of the model
 * @return Current temperature value
 */
double ThermalModelMantsevich::getTemperature() const noexcept {
    return temperature;
}

/**
 * @brief Update model temperature
 * @param heat_input Input heat signal
 * @param dt Time step
 * @return Updated temperature value
 */
double ThermalModelMantsevich::update(double heat_input, double dt) noexcept {
    // simple integrator dynamic model: temperature += heat_input * dt
    temperature += heat_input * dt;
    return temperature;
}