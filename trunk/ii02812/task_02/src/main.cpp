#include <iostream>
#include <limits>
#include <string>
#include "functions.h"

template <typename N>
void Number_Check(N& number, const std::string& message) {
    std::cout << message;
    while (!(std::cin >> number)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input correct number: ";
    }
}

int main() {
    double y_lin_prev = 0, y_lin_next = 0, u = 0, u_prev = 0;
    double a = 0, b = 0, c = 0, d = 0;
    int n = 0;

    Number_Check(y_lin_prev, "Enter input temperature (y): ");
    Number_Check(u, "Enter input warm (u): ");
    double y_nonlin_0 = 0;
    double y_nonlin_1 = y_lin_prev;
    double y_nonlin_2 = 0;
    Number_Check(a, "Enter constant a: ");
    Number_Check(b, "Enter constant b: ");
    Number_Check(c, "Enter constant c: ");
    Number_Check(d, "Enter constant d: ");
    Number_Check(n, "Enter an amount of steps (n): ");

    std::cout << "\nSimulation start:\n";
    for (int i = 1; i <= n; i++) {
        y_lin_next = linear_model(a, b, y_lin_prev, u);
        y_lin_prev = y_lin_next;

        y_nonlin_2 = nonlinear_model(a, b, c, d, y_nonlin_0, y_nonlin_1, u, u_prev);

        y_nonlin_0 = y_nonlin_1;
        y_nonlin_1 = y_nonlin_2;
        u_prev = u;

        std::cout << "Step " << i
            << ": linear = " << y_lin_next
            << ", nonlinear = " << y_nonlin_2 << std::endl;
    }

    std::cout << "Simulation finished.\n";
    return 0;
}
