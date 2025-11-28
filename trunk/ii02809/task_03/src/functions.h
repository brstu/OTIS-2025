#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/**
 * @brief Calculates the next state for the linear model.
 * @param y Current state.
 * @param u Control input.
 * @param a Model parameter a.
 * @param b Model parameter b.
 * @return Next state y_next.
 */
double linear(double y, double u, double a, double b);

/**
 * @brief Calculates the next state for the nonlinear model.
 * @param y Current state.
 * @param u Control input.
 * @param a Model parameter a.
 * @param b Model parameter b.
 * @param c Model parameter c.
 * @param d Model parameter d.
 * @return Next state y_next.
 */
double nonlinear(double y, double u, double a, double b, double c, double d);

/**
 * @brief PID controller class for discrete PID regulation.
 */
class PID {
public:
    /**
     * @brief Constructor to initialize PID parameters.
     * @param K Proportional gain.
     * @param Ti Integration time constant.
     * @param Td Differentiation time constant.
     * @param To Sampling time.
     */
    PID(double K, double Ti, double Td, double To);

    /**
     * @brief Computes the control output u(k) based on error e(k).
     * @param e Current error.
     * @return Control output u(k).
     */
    double compute(double e);

private:
    double q0, q1, q2;
    double e_prev, e_prev2;
    double u_prev;
};

#endif