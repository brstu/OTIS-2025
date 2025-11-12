#include <iostream>
#include <vector>

struct ModelParams {
    double a;
    double b;
    double c;
    double d;
};

// Линейная модель
inline double linear_model(double y_prev, double u, const ModelParams& p) {
    return p.a * y_prev + p.b * u;
}

// Нелинейная модель
inline double nonlinear_model(double y_prev, double y_prev_2, double u, const ModelParams& p) {
    return p.a * y_prev - p.b * std::pow(y_prev_2, 2) + p.c * u + p.d * std::sin(u);
}

//void run_simulation() {
//    ModelParams params;
//    double u;
//    int num_steps;
//    int model_choice;
//    double y_1;
//    double y_2;
//
//    std::cout << "Enter coefficient a: ";
//    std::cin >> params.a;
//    std::cout << "Enter coefficient b: ";
//    std::cin >> params.b;
//    std::cout << "Enter coefficient c: ";
//    std::cin >> params.c;
//    std::cout << "Enter coefficient d: ";
//    std::cin >> params.d;
//
//    std::cout << "Enter the supplied heat u: ";
//    std::cin >> u;
//
//    std::cout << "Enter the initial temperature y_1: ";
//    std::cin >> y_1;
//
//    std::cout << "Enter the initial temperature y_2: ";
//    std::cin >> y_2;
//
//    std::cout << "Enter the number of steps for the simulation: ";
//    std::cin >> num_steps;
//
//    std::cout << "Select model (1 – Linear, 2 – Nonlinear): ";
//    std::cin >> model_choice;
//
//    std::vector<double> temperatures(num_steps);
//
//    for (int t = 0; t < num_steps; ++t) {
//        temperatures[t] = y_1;
//
//        if (model_choice == 1) {
//            y_1 = linear_model(y_1, u, params);
//        }
//        else if (model_choice == 2) {
//            double y_next = nonlinear_model(y_1, y_2, u, params);
//            y_2 = y_1;
//            y_1 = y_next;
//        }
//        else {
//            std::cout << "Wrong model choice!" << std::endl;
//            return;
//        }
//    }
//
//    std::cout << "\nTemperature over time:\n";
//    for (int t = 0; t < num_steps; ++t) {
//        std::cout << "Step " << t + 1 << ": " << temperatures[t] << " C" << std::endl;
//    }
//}
//
//int main() {
//    run_simulation();
//
//    system("pause");
//
//    return 0;
//}