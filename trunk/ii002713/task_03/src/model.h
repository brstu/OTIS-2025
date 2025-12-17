#ifndef MODEL_H
#define MODEL_H

/**
 * @brief Simple dynamic model for simulation purposes.
 *
 * The Model class represents a system whose state is described by the variable @c y.
 * The state @c y can be initialized and updated via the provided methods.
 */
class Model {
private:
    /**
     * @brief Current state of the model.
     *
     * Represents the output or state variable of the model.
     */
    double y{0.0};  ///< in-class initialization

public:
    /**
     * @brief Construct the model with an initial state.
     * @param y0 Initial state value (default 0.0)
     */
    explicit Model(double y0 = 0.0) noexcept;

    /**
     * @brief Returns the current state of the model.
     *
     * This method provides read-only access to the current value of the state variable @c y.
     *
     * @return The current value of the state variable @c y.
     */
    double getY() const noexcept;
    /**
     * @brief Updates the state of the model based on the input and time step.
     *
     * This method updates the internal state variable @c y using the provided input signal @p u
     * and the time step @p dt. The specific update rule is defined in the implementation.
     *
     * @param u Input signal to the model, representing the external influence or control input.
     * @param dt Time step for the update, representing the elapsed time since the last update (must be positive).
     * @return The updated value of the state variable @c y after applying the input and time step.
     */
    double update(double u, double dt) noexcept;
};

#endif // MODEL_H
