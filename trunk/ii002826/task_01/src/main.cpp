#include <iostream>
#include <cmath>
#include <vector>

struct ModelParameters {
    double a, b, c, d;
};

double calculate_linear(double current_temp, double heat_input, double coeff_a, double coeff_b) {
    return coeff_a * current_temp + coeff_b * heat_input;
}

double calculate_nonlinear(double temp_t1, double temp_t2, double heat_input, const ModelParameters& params) {
    return params.a * temp_t1 - params.b * std::pow(temp_t2, 2) +
        params.c * heat_input + params.d * std::sin(heat_input);
}

enum ModelType {
    LINEAR = 1,
    NONLINEAR = 2
};

int main() {
    ModelParameters coefficients{};
    double heat_input, initial_temperature;
    int simulation_steps, selected_model;

    std::cout << "Введите коэффициент a: ";
    std::cin >> coefficients.a;
    std::cout << "Введите коэффициент b: ";
    std::cin >> coefficients.b;
    std::cout << "Введите коэффициент c: ";
    std::cin >> coefficients.c;
    std::cout << "Введите коэффициент d: ";
    std::cin >> coefficients.d;

    std::cout << "Введите значение подаваемого тепла u: ";
    std::cin >> heat_input;
    std::cout << "Введите начальную температуру y0: ";
    std::cin >> initial_temperature;
    std::cout << "Введите количество шагов моделирования: ";
    std::cin >> simulation_steps;

    std::cout << "Выберите модель (1 - Линейная, 2 - Нелинейная): ";
    std::cin >> selected_model;

    std::vector<double> temperature_history(simulation_steps);
    double current_temp = initial_temperature;
    double previous_temp = initial_temperature;

    for (int step = 0; step < simulation_steps; ++step) {
        temperature_history[step] = current_temp;

        switch (selected_model) {
        case LINEAR:
            current_temp = calculate_linear(current_temp, heat_input,
                coefficients.a, coefficients.b);
            break;

        case NONLINEAR: {
            double next_temp = calculate_nonlinear(current_temp, previous_temp,
                heat_input, coefficients);
            previous_temp = current_temp;
            current_temp = next_temp;
            break;
        }

        default:
            std::cerr << "Ошибка: выбрана неверная модель!" << std::endl;
            return 1;
        }
    }

    std::cout << "\nРезультаты моделирования температуры:\n";
    for (int step = 0; step < simulation_steps; ++step) {
        std::cout << "Шаг " << step + 1 << ": " << temperature_history[step]
            << " °C" << std::endl;
    }

    return 0;
}