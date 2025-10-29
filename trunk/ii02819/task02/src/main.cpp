#include <iostream>
#include <cmath>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// Параметры регулятора
const double GAIN = 0.001;       // коэффициент усиления
const double T_INT = 50;         // постоянная интегрирования
const double T_DIF = 100;        // постоянная дифференцирования
const double STEP = 1;           // шаг дискретизации

// Коэффициенты модели
const double A = 0.4;
const double B = 0.4;
const double C = 0.4;
const double D = 0.4;

// Функция вычисления управляющего воздействия
double computeControl(double e0, double e1, double e2) {
    double q0 = GAIN * (1.0 + T_DIF / STEP);
    double q1 = -GAIN * (1.0 + 2.0 * T_DIF / STEP - STEP / T_INT);
    double q2 = GAIN * T_DIF / STEP;
    return q0 * e0 + q1 * e1 + q2 * e2;
}

// Моделирование системы
void runSimulation(double target) {
    vector<double> y = {0.0, 0.0, 0.0};   // выход системы
    vector<double> u = {1.0, 1.0};        // управляющее воздействие

    for (int k = 0; k < static_cast<int>(T_INT); ++k) {
        double e0 = target - y[y.size() - 1];
        double e1 = target - y[y.size() - 2];
        double e2 = target - y[y.size() - 3];

        double delta = computeControl(e0, e1, e2);

        u[0] = u[1] + delta;
        u[1] = u[0];

        double nextY = A * y.back()
                     - B * std::pow(y[y.size() - 2], 2)
                     + C * u[0]
                     + D * std::sin(u[1]);

        y.push_back(nextY);
    }

    // Нормализация и вывод
    double last = y.back();
    for (double val : y) {
        cout << val * target / last << endl;
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    double desired;
    cout << "Введите целевое значение: ";
    cin >> desired;
    runSimulation(desired);
    return 0;
}
