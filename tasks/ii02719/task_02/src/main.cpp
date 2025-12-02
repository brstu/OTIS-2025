#include <iostream>
#include <vector>
#include <cmath>
#include "module.h"
using namespace std;

int main() {

    int N;
    std::cout << "Enter number of steps N (N < 100): ";
    std::cin >> N;
    if (N >= 100) {
        std::cout << "Error: out of bounds\n";
        return 1;
    }

    double a, b, c, d;
    std::cout << "Enter constants a, b, c, d: ";
    std::cin >> a >> b >> c >> d;

    std::vector<double> u(N);
    std::cout << "Enter values of u(t) for t = 0.." << N - 1 << ":\n";
    for (int t = 0; t < N; ++t) {
        std::cout << "u[" << t << "] = ";
        std::cin >> u[t];
    }

    std::vector<double> y_lin(N + 1);
    std::vector<double> y_nl(N + 1);

    std::cout << "Enter initial temperature y[0]: ";
    std::cin >> y_lin[0];
    y_nl[0] = y_lin[0];

    std::cout << "Enter y[1] for nonlinear model: ";
    std::cin >> y_nl[1];

    // Linear model
    compute_linear(N, a, b, u, y_lin);

    // Nonlinear model
    compute_nonlinear(N, a, b, c, d, u, y_nl);

    std::cout << "\nSimulation results:\n";
    std::cout << "t  y_lin  y_nl\n";
    for (int t = 0; t <= N; ++t) {
        std::cout << t << "  " << y_lin[t] << "  " << y_nl[t] << "\n";
    }

    return 0;
}


