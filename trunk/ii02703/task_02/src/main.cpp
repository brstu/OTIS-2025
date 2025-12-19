#include <iostream>
#include "models.hpp" 

int main() {
    double y, u, a, b, c, d;
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
        y_lin = linear_model(y_lin, u, a, b);
        std::cout << "Step " << i + 1 << ": " << y_lin << std::endl;
    }


    double y_curr = y;
    double y_prev_nl = y;
    double u_prev_nl = u;
    std::cout << "\nNonlinear model:\n";

    for (int i = 0; i < n; i++) {
        double y_next = nonlinear_model(y_curr, y_prev_nl, u, u_prev_nl, a, b, c, d);

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