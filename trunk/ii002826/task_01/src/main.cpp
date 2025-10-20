#include <iostream>
#include <cmath>
#include <vector>


// Линейная модель
double linear_model(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

// Нелинейная модель
double nonlinear_model(double y_prev, double y_prev_2, double u, double a, double b, double c, double d) {
    return a * y_prev - b * pow(y_prev_2, 2) + c * u + d * sin(u);
}

int main() {
    double a, b, c, d;
    double u;
    double y_0;
    int num_steps;
    int model_choice;

    // Ввод параметров пользователем
    std::cout << "Enter coefficient a: ";
    std::cin >> a;
    std::cout << "Enter coefficient b: ";
    std::cin >> b;
    std::cout << "Enter coefficient c: ";
    std::cin >> c;
    std::cout << "Enter coefficient d: ";
    std::cin >> d;

    std::cout << "Enter the supplied heat u: ";
    std::cin >> u;

    std::cout << "Enter the initial temperature y_0: ";
        std::cin >> y_0;

    std::cout << "Enter the number of steps for the simulation : ";
    std::cin >> num_steps;

    std::cout << "Select model(1 – Linear, 2 – Nonlinear) : ";
    std::cin >> model_choice;

    vector<double> temperatures(num_steps);

    // Инициализация начальных значений
    double y_1 = y_0;  // y[t]
    double y_2 = y_0;  // y[t-1] (нужно для нелинейной модели)

    for (int t = 0; t < num_steps; ++t) {
        temperatures[t] = y_1;

        if (model_choice == 1) {
            y_1 = linear_model(y_1, u, a, b);
        }
        else if (model_choice == 2) {
            double y_next = nonlinear_model(y_1, y_2, u, a, b, c, d);
            y_2 = y_1;  // обновляем y[t-1]
            y_1 = y_next;
        }
        else {
            std::cout << "Wrong model choice!" << endl;
            return -1;
        }
    }

    // Вывод результатов
    std::cout << "\nTemperature over time:\n";
    for (int t = 0; t < num_steps; ++t) {
        std::cout << "Step " << t + 1 << ": " << temperatures[t] << " C" << endl;
    }

    return 0;
}