#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int max_steps = 100;

    int steps;
    std::cout << "enter steps: ";
    std::cin >> steps;

    if (steps > max_steps || steps < 2) {
        std::cout << "incorrect: \n";
        return 1;
    }

    double a;
    double b;
    double c;
    double d;

    std::cout << "enter a: \n";
    std::cin >> a;

    std::cout << "enter b: \n";
    std::cin >> b;

    std::cout << "enter c: \n";
    std::cin >> c;

    std::cout << "enter d: \n";
    std::cin >> d;

    std::vector<long double> y(steps + 1);
    std::vector<double> u(steps);

    std::cout << "enter y0: \n";
    std::cin >> y[0];

    std::cout << "enter y1: \n";
    std::cin >> y[1];

    std::cout << "enter u: \n";
    for (int t = 0; t < steps; ++t) {
        std::cout << "u[" << t << "] = ";
        std::cin >> u[t];
    }

    int model;
    std::cout << "choose model: 1-linear; 2-non-linear\n";
    std::cin >> model;

    for (int t = 1; t < steps; t++) {
        if (model == 1) {
            y[t + 1] = a * y[t] + b * u[t];
        } else {
            y[t + 1] = a * y[t] - b * y[t - 1] * y[t - 1] + c * u[t] + d * std::sin(u[t - 1]);
        }
    }

    for (int t = 0; t <= steps; t++) {
        std::cout << "step " << t << ": y = " << y[t] << "\n";
    }

    return 0;
}
