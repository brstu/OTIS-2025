#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

// Генератор целых случайных чисел в диапазоне [min, max]
int randomIntInRange(int min, int max) {
    std::random_device rd;                  
    std::uniform_int_distribution dis(min, max); 
    return dis(rd);                         
}

void input(int& k, vector<double>& u, vector<double>& y, double& a, double& b, double& c, double& d) {
    cout << "Enter number of iterations: ";
    cin >> k;

    u.resize(k + 5, 0);
    y.resize(k + 5, 0);

    cout << "\nEnter initial temperature: ";
    cin >> y[0];

    cout << "Enter second temperature value (for nonlinear model): ";
    cin >> y[1];

    cout << "\nGenerating warm values (random integer 5-20)...\n";
    for (int i = 0; i < k; i++) {
        u[i] = randomIntInRange(5, 20);
        cout << "warm[" << i << "] = " << (int)u[i] << endl;
    }

    cout << "\nEnter constants:\n";
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;
    cout << "d = ";
    cin >> d;
}

void linear(const int tau, vector<double>& y, const vector<double>& u, const double& a, const double& b) {
    y[tau + 1] = a * y[tau] + b * u[tau];
}

void nonlinear(const int tau, vector<double>& y, const vector<double>& u,
    const double& a, const double& b, const double& c, const double& d) {
    y[tau + 1] = a * y[tau] - b * y[tau - 1] * y[tau - 1] + c * u[tau] + d * sin(u[tau - 1]);
}

// Функция для сохранения данных в файл для построения графика
void saveDataToFile(const vector<double>& time, const vector<double>& linear_data,
    const vector<double>& nonlinear_data, const vector<double>& warm) {
    ofstream file("graph_data.txt");

    if (!file.is_open()) {
        cerr << "Error: Cannot create data file!" << endl;
        return;
    }

    // Заголовок файла
    file << "Time\tLinear_Temp\tNonlinear_Temp\tWarm\n";

    // Данные
    for (size_t i = 0; i < time.size(); i++) {
        file << time[i] << "\t" << linear_data[i] << "\t"
            << nonlinear_data[i] << "\t" << warm[i] << "\n";
    }

    file.close();
    cout << "\nData saved to 'graph_data.txt'" << endl;
}

int main() {
    int k;
    vector<double> y_lin;
    vector<double> y_nonlin;
    vector<double> u;
    double a;
    double b;
    double c;
    double d;

    input(k, u, y_lin, a, b, c, d);
    y_nonlin = y_lin;

    cout << "\n=== CALCULATIONS ===\n";

    // Линейная модель
    cout << "\nLinear model:\n";
    for (int tau = 0; tau < k - 1; tau++) {
        linear(tau, y_lin, u, a, b);
    }

    for (int i = 0; i < k; i++) {
        cout << "Time " << i << ": warm = " << (int)u[i]
            << ", temperature = " << y_lin[i] << endl;
    }

    // Нелинейная модель
    cout << "\nNonlinear model:\n";
    for (int tau = 1; tau < k - 1; tau++) {
        nonlinear(tau, y_nonlin, u, a, b, c, d);
    }

    for (int i = 0; i < k; i++) {
        cout << "Time " << i << ": warm = " << (int)u[i]
            << ", temperature = " << y_nonlin[i] << endl;
    }

    // Сохраняем данные для графика
    vector<double> time_points(k);
    for (int i = 0; i < k; i++) {
        time_points[i] = i;
    }

    saveDataToFile(time_points, y_lin, y_nonlin, u);

    // Запускаем Python скрипт для построения графика
    cout << "\nGenerating graph...\n";
    system("python plot_graph.py");

    return 0;
}
