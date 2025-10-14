#include <iostream>
#include <vector>
#include <cmath>



const std::vector<double> params{ 0.8, 0.6, 0.4, 2.2 };
const double heat_input = 0.8;

std::vector<double> linearSim(int n, double start_temp) {
    std::vector<double> data(n);
    data[0] = start_temp;

    for (int i = 1; i < n; i++) {
        data[i] = params[0] * data[i - 1] + params[1] * heat_input;
    }
    return data;
}

std::vector<double> nonlinearSim(int n, double start_temp) {
    std::vector<double> data(n);
    data[0] = start_temp;

    if (n > 1) {
        data[1] = params[0] * data[0] + params[2] * heat_input + params[3] * sin(heat_input);
    }

    for (int i = 2; i < n; i++) {
        data[i] = params[0] * data[i - 1] - params[1] * data[i - 2] * data[i - 2]
            + params[2] * heat_input + params[3] * sin(heat_input);
    }
    return data;
}

int main() {
    double start_temp;
    int steps;

    std::cout << "Enter starting temperature: ";
    std::cin >> start_temp;

    std::cout << "Enter number of steps: ";
    std::cin >> steps;

    while (steps < 1) {
        std::cout << "Steps must be 1 or more: ";
        std::cin >> steps;
    }

    std::vector<double> linear_data = linearSim(steps, start_temp);
    std::vector<double> nonlinear_data = nonlinearSim(steps, start_temp);

    std::cout << "\nLinear Model Results:" << std::endl;
    for (int i = 0; i < steps; i++) {
        std::cout << "Step " << i << ": " << linear_data[i] << std::endl;
    }

    std::cout << "\nNonlinear Model Results:" << std::endl;
    for (int i = 0; i < steps; i++) {
        std::cout << "Step " << i << ": " << nonlinear_data[i] << std::endl;
    }

    return 0;
}
