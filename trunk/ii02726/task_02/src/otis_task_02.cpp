#include <iostream>
#include <cmath>
#include "test.h"



int main() {
    int max_steps = 100;
    int steps;
    double a;
    double b;
    double c;
    double d;
    double y0;
    double y1;

    std::cout << "enter steps: ";
    std::cin >> steps;
    if (steps > max_steps || steps < 2) {
        std::cout << "Error: steps must be between 2 and 100: \n";
        return 1;
    }

    std::cout << "enter a: \n";
    std::cin >> a;

    std::cout << "enter b: \n";
    std::cin >> b;

    std::cout << "enter c: \n";
    std::cin >> c;

    std::cout << "enter d: \n";
    std::cin >> d;

    std::cout << "enter y0: \n";
    std::cin >> y0;

    std::cout << "enter y1: \n";
    std::cin >> y1;

    std::cout << "enter u: \n";
    std::vector<double> u(steps);
    for (int i = 0; i < steps; i++) {
        std::cout << "u[" << i << "] = ";
        std::cin >> u[i];
    }

    int model;
    std::cout << "choose model: 1-linear; 2-non-linear\n";
    std::cin >> model;

    std::vector<double> y;
    const abcd str_fun {a,b,c,d};

    if (model == 1) {
        y = linear_func(steps, a, b, u, y0, y1);
    } else {
        y = nonlinear_func(steps, str_fun, u, y0, y1);
    }

    for (int i = 0; i < steps; i++) {
        std::cout << "step " << i << ": y = " << y[i] << "\n";
    }

    return 0;
}
