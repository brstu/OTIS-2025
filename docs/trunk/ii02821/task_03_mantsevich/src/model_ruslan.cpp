/**
 * @file model_ruslan.cpp
 * @brief Implementation of dynamic model class
 * @author Ruslan
 * @date 2024
 */

#include "model_ruslan.h"

/**
 * @brief Constructor for dynamic model
 * @param y0 Initial state value
 */
Model_ruslan::Model_ruslan(double y0) noexcept
    : y(y0) {}

/**
 * @brief Get current state of the model
 * @return Current state value
 */
double Model_ruslan::getY() const noexcept {
    return y;
}

/**
 * @brief Update model state
 * @param u Input control signal
 * @param dt Time step
 * @return Updated state value
 */
double Model_ruslan::update(double u, double dt) noexcept {
    // simple integrator dynamic model: y += u * dt
    y += u * dt;
    return y;
}