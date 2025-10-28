#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Константы системы управления
const double k_gain = 0.001;                  // коэффициент усиления
const double k_integration = 50;              // постоянная интегрирования
const double k_differentiation = 100;         // постоянная дифференцирования
const double k_step = 1;                      // шаг дискретизации
const double coeff_a = 0.4;
const double coeff_b = 0.4;
const double coeff_c = 0.4;
const double coeff_d = 0.4;

// Моделирование нелинейной системы
void simulateNonlinearSystem(double target_value) {
    double factor_q0 = k_gain * (1 + k_differentiation / k_step);
    double factor_q1 = -k_gain * (1 + 2 * k_differentiation / k_step - k_step / k_integration);
    double factor_q2 = k_gain * k_differentiation / k_step;

    vector<double> system_output = {0, 0, 0};
    vector<double> control_input = {1, 1};

    for (int iteration = 0; iteration < k_integration; iteration++) {
        double error_curr = target_value - system_output[system_output.size() - 1];
        double error_prev1 = target_value - system_output[system_output.size() - 2];
        double error_prev2 = target_value - system_output[system_output.size() - 3];

        double correction = factor_q0 * error_curr + factor_q1 * error_prev1 + factor_q2 * error_prev2;

        control_input[0] = control_input[1] + correction;
        control_input[1] = control_input[0];

        system_output.push_back(
            coeff_a * system_output[system_output.size() - 1] -
            coeff_b * pow(system_output[system_output.size() - 2], 2) +
            coeff_c * control_input[0] +
            coeff_d * sin(control_input[1])
        );
    }

    for (double value : system_output) {
        double normalized = value * target_value / system_output.back();
        cout << normalized << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    double user_target;
    cout << "Введите желаемое значение: ";
    cin >> user_target;
    simulateNonlinearSystem(user_target);
    return 0;
}
