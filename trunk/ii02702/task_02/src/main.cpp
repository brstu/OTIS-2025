#include <iostream>
#include "models.hpp"

int main() {
    const double y = 0;        // начальное значение выходной переменной (состояние системы)
    const double u = 1;        // входное воздействие (управляющий сигнал)
    const int t = 10;          // время симуляции (количество шагов)

    double linear_a = 0.4;     // коэффициент при предыдущем значении y
    double linear_b = 0.5;     // коэффициент при входном воздействии u

    double nonlinear_a = 0.5;  // линейный коэффициент при y
    double nonlinear_b = 0.5;  // коэффициент при квадрате предыдущего значения y (нелинейность)
    double nonlinear_c = 0.3;  // коэффициент при входном воздействии u
    double nonlinear_d = 0.5;  // коэффициент при синусоидальном члене
    
    std::cout << "Linear simulation:" << std::endl;
    std::vector<double> linear = simulateLinearModel(y, u, t, linear_a, linear_b);
    for (const auto& value : linear) {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl;
    std::vector<double> nonlinear = simulateNonLinearModel(y, u, t, nonlinear_a, nonlinear_b, nonlinear_c, nonlinear_d);
    for (const auto& value : nonlinear) {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;

    return 0;
}