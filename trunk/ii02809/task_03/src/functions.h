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
 * @brief PID controller class (velocity-form/discrete implementation).
 */
class PID
{
public:
    /**
     * @brief Constructor to initialize PID coefficients.
     * @param K   Proportional gain.
     * @param Ti  Integration time constant.
     * @param Td  Differentiation time constant.
     * @param To  Sampling period.
     */
    PID(double K, double Ti, double Td, double To);

    /**
     * @brief Computes the control output increment and returns the new u(k).
     * @param e Current error e(k) = r(k) - y(k).
     * @return Control output u(k).
     */
    double compute(double e);

private:
    double q0;
    double q1;
    double q2;

    double e_prev  { 0.0 };
    double e_prev2 { 0.0 };
    double u_prev  { 0.0 };
};

#endif // FUNCTIONS_H
