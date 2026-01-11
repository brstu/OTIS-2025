#include <iostream>
#include "model.hpp"

int main() {
    double y;
    double u;
    double a;
    double b;
    double c;
    double d;
    int n;

    std::cout << "Enter y(starting temperature) and u(input warm at every step): ";
    std::cin >> y >> u;

    std::cout << "Enter a, b, c, d(constants): ";
    std::cin >> a >> b >> c >> d;

    std::cout << "Enter step count n: ";
    std::cin >> n;

    double y_prev = y;

    // Linear model
    for (int i = 0; i < n; i++) {
        y = computeLinear(y, u, a, b);
        std::cout << "Linear step " << i+1 << ": " << y << "\n";
    }

    // Nonlinear model
    double original_y = y_prev;
    y = original_y;
    double y_prev2 = 0;

    for (int i = 0; i < n; i++) {
        std::cout << "Nonlinear step " << i+1 << ": " << y << "\n";
        double y_next = computeNonlinear(y, y_prev2, u, a, b, c, d);
        y_prev2 = y;
        y = y_next;
    }

    return 0;
}
