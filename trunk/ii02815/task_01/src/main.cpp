#include <iostream>
#include <cmath>

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

int main() {
    double a;
    double b;
    double c;
    double d;
    double y0;
    double u0;
    int n;

    std::cout << "Enter constants a, b, c, d: ";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> d;

    std::cout << "Enter initial output y0: ";
    std::cin >> y0;

    std::cout << "Enter initial input u0: ";
    std::cin >> u0;

    std::cout << "Enter number of steps (n): ";
    std::cin >> n;

    ModelParameters params{a, b, c, d};

    double y_linear_current = y0;
    double y_nonlinear_current = y0;
    double y_nonlinear_previous = y0;

    double u_previous = u0;
    double u_current;

    std::cout << "Steps\tLinear model\tNonlinear model\n";

    for (int step = 1; step <= n; ++step) {
        std::cout << "Enter input u for step " << step << ": ";
        std::cin >> u_current;
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