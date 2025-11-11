#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

struct ModelParameters {
    double a;
    double b;
    double c;
    double d;
};

double linearModel(double y_current, double u_current, const ModelParameters& params) {
    return params.a * y_current + params.b * u_current;
}

double nonlinearModel(double y_current, double y_previous, double u_current, double u_previous, const ModelParameters& params) {
    return params.a * y_current - params.b * y_previous * y_previous + params.c * u_current + params.d * sin(u_previous);
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void readDouble(const std::string& text, double& value) {
    while (true) {
        std::cout << text;
        if (std::cin >> value) {
            return;
        }
        else {
            std::cout << "Invalid input. Please enter a numeric value.\n";
            clearInput();
        }
    }
}

void readPositiveInt(const std::string& text, int& value) {
    while (true) {
        std::cout << text;
        if (std::cin >> value && value > 0) {
            return;
        }
        else {
            std::cout << "Invalid input. Please enter a positive integer.\n";
            clearInput();
        }
    }
}

int main() {
    double a;
    double b;
    double c;
    double d;
    double y0;
    double u0;
    int n;

    readDouble("Enter constant a: ", a);
    readDouble("Enter constant b: ", b);
    readDouble("Enter constant c: ", c);
    readDouble("Enter constant d: ", d);
    readDouble("Enter initial output y0: ", y0);
    readDouble("Enter initial input u0: ", u0);
    readPositiveInt("Enter number of steps (n): ", n);

    std::vector<double> u_values(n + 1); 
    u_values[0] = u0;

    std::cout << "Enter input u for:\n";
    for (int i = 1; i <= n; ++i) {
        readDouble("Step " + std::to_string(i) + ": ", u_values[i]);
    }

    ModelParameters params{ a, b, c, d };

    double y_linear_current = y0;
    double y_nonlinear_current = y0;
    double y_nonlinear_previous = y0;
    double u_previous = u0;
    double u_current;

    std::cout << "Steps\tLinear model\tNonlinear model\n";
    for (int step = 1; step <= n; ++step) {
        u_current = u_values[step];
        double linear_result = linearModel(y_linear_current, u_current, params);
        double nonlinear_result = nonlinearModel(y_nonlinear_current, y_nonlinear_previous, u_current, u_previous, params);

        std::cout << step << "\t" << linear_result << "\t\t" << nonlinear_result << "\n";

        y_linear_current = linear_result;
        y_nonlinear_previous = y_nonlinear_current;
        y_nonlinear_current = nonlinear_result;
        u_previous = u_current;
    }
    return 0;
}