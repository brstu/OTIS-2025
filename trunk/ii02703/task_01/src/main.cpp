#include <iostream>
#include <cmath>

int main() {
    double y;
    double u;
    double a;
    double b;
    double c;
    double d;

    int n;

    std::cout << "Enter start temperature and heat: ";
    std::cin >> y >> u;
    std::cout << "Enter a, b, c, d: ";
    std::cin >> a >> b >> c >> d;
    std::cout << "Steps: ";
    std::cin >> n;


    double y_lin = y;
    std::cout << "\nLinear model:\n";
    for (int i = 0; i < n; i++) {
        y_lin = a * y_lin + b * u;
        std::cout << "Step " << i + 1 << ": " << y_lin << std::endl;
    }


    double y_curr = y;
    double y_prev_nl = y;
    double u_prev_nl = u;
    std::cout << "\nNonlinear model:\n";

    for (int i = 0; i < n; i++) {
        double y_next = a * y_curr - b * (y_prev_nl * y_prev_nl) + c * u + d * sin(u_prev_nl);

        y_prev_nl = y_curr;
        y_curr = y_next;
        u_prev_nl = u;

        std::cout << "Step " << i + 1 << ": " << y_curr << std::endl;

        if (i < n - 1) {
            std::cout << "Enter next heat: ";
            std::cin >> u;
        }
    }

    return 0;
}