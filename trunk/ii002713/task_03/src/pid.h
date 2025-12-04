#ifndef PID_H
#define PID_H

#include <limits>

/**
 * @class PID
 * @brief Proportional-Integral-Derivative (PID) controller class.
 *
 * Provides basic PID control functionality with configurable gains,
 * output limits, and integral anti-windup protection.
 */
class PID {
public:
    /**
     * @brief Constructs a PID controller with specified gains and time step.
     * @param Kp_ Proportional gain.
     * @param Ki_ Integral gain.
     * @param Kd_ Derivative gain.
     * @param dt_ Time step (in seconds).
     */
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = DEFAULT_DT);
    /**
     * @brief Computes the PID controller output for the given setpoint and measured value.
     * @param setpoint The desired target value.
     * @param measured The current measured value.
     * @return The control output computed by the PID algorithm.
     *
     * This method updates the internal state (integral and previous error).
     */
    double compute(double setpoint, double measured) noexcept;
    /**
     * @brief Resets the internal state of the PID controller.
     *
     * This clears the integral term and previous error.
     */
    void reset() noexcept;
    /**
     * @brief Sets the minimum and maximum output limits for the controller.
     * @param min Minimum output value.
     * @param max Maximum output value.
     *
     * The output will be clamped to this range.
     */
    void setOutputLimits(double min, double max);
    /**
     * @brief Sets the minimum and maximum limits for the integral term (anti-windup).
     * @param min Minimum integral value.
     * @param max Maximum integral value.
     *
     * The integral term will be clamped to this range.
     */
    void setIntegralLimits(double min, double max);
    /**
     * @brief Sets the time step (dt) for the PID controller.
     * @param new_dt New time step value (in seconds).
     */
    void setDt(double new_dt);

private:
    double Kp;
    double Ki;
    double Kd;

    double dt;
    double inv_dt;

    double prev_error = 0.0;
    double integral = 0.0;
    bool prev_error_initialized = false;

    double output_min = -std::numeric_limits<double>::infinity();
    double output_max =  std::numeric_limits<double>::infinity();
    double integral_min = -std::numeric_limits<double>::infinity();
    double integral_max =  std::numeric_limits<double>::infinity();

    static constexpr double DEFAULT_DT = 0.01;
};

#endif // PID_H
