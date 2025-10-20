#include <iostream>
#include <cmath>
#include <vector>

// Константы для выбора модели
const int LINEAR_MODEL = 1;
const int NONLINEAR_MODEL = 2;

// Линейная модель
double linear_model(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

// Нелинейная модель
double nonlinear_model(double y_prev, double y_prev_2, double u, double a, double b, double c, double d) {
    return a * y_prev - b * std::pow(y_prev_2, 2) + c * u + d * std::sin(u);
}

// Проверка корректности ввода
bool read_double(const std::string& prompt, double& value) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
        std::cerr << "Invalid input. Please enter a numeric value." << std::endl;
        return false;
    }
    return true;
}

bool read_int(const std::string& prompt, int& value) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
        std::cerr << "Invalid input. Please enter an integer." << std::endl;
        return false;
    }
    return true;
}

// Симуляция процесса
void simulate(int model_choice, double a, double b, double c, double d, double u, double y_0, int num_steps) {
    std::vector<double> temperatures(num_steps);

    double y_1 = y_0; // y[t]
    double y_2 = y_0; // y[t-1]

    for (int t = 0; t < num_steps; ++t) {
        temperatures[t] = y_1;

        if (model_choice == LINEAR_MODEL) {
            y_1 = linear_model(y_1, u, a, b);
        }
        else if (model_choice == NONLINEAR_MODEL) {
            double y_next = nonlinear_model(y_1, y_2, u, a, b, c, d);
            y_2 = y_1;
            y_1 = y_next;
        }
        else {
            std::cerr << "Invalid model choice!" << std::endl;
            return;
        }
    }

    // Вывод результатов
    std::cout << "\nTemperature over time:\n";
    for (int t = 0; t < num_steps; ++t) {
        std::cout << "Step " << t + 1 << ": " << temperatures[t] << " C" << std::endl;
    }
}

int main() {
    double a, b, c, d, u, y_0;
    int num_steps;
    int model_choice;

    // Безопасный ввод данных
    if (!read_double("Enter coefficient a: ", a)) return 1;
    if (!read_double("Enter coefficient b: ", b)) return 1;
    if (!read_double("Enter coefficient c: ", c)) return 1;
    if (!read_double("Enter coefficient d: ", d)) return 1;
    if (!read_double("Enter the supplied heat u: ", u)) return 1;
    if (!read_double("Enter the initial temperature y_0: ", y_0)) return 1;
    if (!read_int("Enter the number of steps for the simulation: ", num_steps)) return 1;
    if (!read_int("Select model (1 – Linear, 2 – Nonlinear): ", model_choice)) return 1;

    simulate(model_choice, a, b, c, d, u, y_0, num_steps);

    return 0;
}

