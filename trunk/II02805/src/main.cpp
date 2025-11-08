#include <iostream>
#include <cmath>

double linear_step(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinear_step(double y, double y_prev, double u, double u_prev, double a, double b, double c, double d) {
    return a * y - b * y_prev * y_prev + c * u + d * sin(u_prev);
}

int main() {
    double y, y_prev, y_next;
    double u, u_prev;
    double a, b, c, d;
    int n;

    std::cout << "Enter y (starting temperature) and u (input warmth at first step) values (space-separated): ";
    std::cin >> y >> u;

    std::cout << "Enter a, b, c, d (constants) values: ";
    std::cin >> a >> b >> c >> d;

    std::cout << "Enter number of steps n: ";
    std::cin >> n;

    y_prev = y;
    for (int i = 0; i < n; ++i) {
        y = linear_step(y, u, a, b);
        std::cout << "Result of the " << i + 1 << " step of linear model: " << y << '\n';
    }


    y_prev = 0;
    u_prev = u;

    for (int i = 0; i < n; ++i) {
        y_next = nonlinear_step(y, y_prev, u, u_prev, a, b, c, d);
        y_prev = y;
        y = y_next;

        std::cout << "Result of the " << i + 1 << " step of non-linear model: " << y << '\n';

        u_prev = u;
        std::cout << "Enter u for the " << i + 1 << " step: ";
        std::cin >> u;
    }

    return 0;
}
