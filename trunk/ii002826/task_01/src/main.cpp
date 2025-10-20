#include <iostream>
#include <cmath>
#include <vector>

struct ModelParams {
    double a;
    double b;
    double c;
    double d;
};

// Линейная модель
double linear_model(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

// Нелинейная модель
double nonlinear_model(double y_prev, double y_prev_2, double u, const ModelParams& p) {
    return p.a * y_prev - p.b * std::pow(y_prev_2, 2) + p.c * u + p.d * std::sin(u);
}

int main() {
    ModelParams params{};
    double u;
    double y_0;
    int num_steps;
    int model_choice;

    std::cout << "Enter coefficient a: ";
    std::cin >> params.a;
    std::cout << "Enter coefficient b: ";
    std::cin >> params.b;
    std::cout << "Enter coefficient c: ";
    std::cin >> params.c;
    std::cout << "Enter coefficient d: ";
    std::cin >> params.d;

    std::cout << "Enter the supplied heat u: ";
    std::cin >> u;

    std::cout << "Enter the initial temperature y_0: ";
    std::cin >> y_0;

    std::cout << "Enter the number of steps for the simulation: ";
    std::cin >> num_steps;

    std::cout << "Select model (1 – Linear, 2 – Nonlinear): ";
    std::cin >> model_choice;

    std::vector<double> temperatures(num_steps);

    double y_1 = y_0;
    double y_2 = y_0;

    for (int t = 0; t < num_steps; ++t) {
        temperatures[t] = y_1;

        if (model_choice == 1) {
            y_1 = linear_model(y_1, u, params.a, params.b);
        }
        else if (model_choice == 2) {
            double y_next = nonlinear_model(y_1, y_2, u, params);
            y_2 = y_1;
            y_1 = y_next;
        }
        else {
            std::cout << "Wrong model choice!" << std::endl;
            return -1;
        }
    }

    std::cout << "\nTemperature over time:\n";
    for (int t = 0; t < num_steps; ++t) {
        std::cout << "Step " << t + 1 << ": " << temperatures[t] << " C" << std::endl;
    }

    return 0;
}

