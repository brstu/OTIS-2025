#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

struct ModelParameters {
    double a1;
    double b;
    double c;
    double d;
};

double computeLinear(double y1, double u1, double a1, double b1) {
    return a1 * y1 + b1 * u1;
}

double computeNonLinear(double y, double& prev_y, double u, const ModelParameters& params) {
    double result = params.a1 * y - params.b * prev_y * prev_y + params.c * u + params.d * std::sin(u);
    prev_y = y;
    return result;
}

void simulateModel(int steps, double u, const ModelParameters& params, double init_y_linear, double init_y_nonlinear, double init_prev_y) {

    std::cout << "\nSimulation Results:\n";
    std::cout << std::string(50, '-') << std::endl;

    double y_linear = init_y_linear;
    double y_nonlinear = init_y_nonlinear;
    double prev_y_nonlinear = init_prev_y;

    for (int step = 0; step < steps; ++step) {
        y_linear = computeLinear(y_linear, u, params.a1, params.b);
        y_nonlinear = computeNonLinear(y_nonlinear, prev_y_nonlinear, u, params);

        std::format << "Step " << std::setw(2) << step << ": ";
        std::format << "Linear = " << std::setw(10) << std::fixed << std::setprecision(4) << y_linear;
        std::cout << " | Non-linear = " << std::setw(10) << y_nonlinear << std::endl;
    }
}

int main() {
    double y_current;
    double y_previous;
    double u_input;
    std::cout << "Enter initial conditions (Y_{n-1}, Y_n, U): ";
    std::cin >> y_previous >> y_current >> u_input;

    ModelParameters params;
    std::cout << "Enter model parameters (A, B, C, D): ";
    std::cin >> params.a1 >> params.b >> params.c >> params.d;

    int num_steps;
    std::cout << "Enter number of simulation steps: ";
    std::cin >> num_steps;

    simulateModel(num_steps, u_input, params, y_current, y_current, y_previous);

    return 0;
}