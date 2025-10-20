#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Линейная модель
double linear_model(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

// Нелинейная модель
double nonlinear_model(double y_prev, double y_prev_2, double u, double a, double b, double c, double d) {
    return a * y_prev - b * pow(y_prev_2, 2) + c * u + d * sin(u);
}

int main() {
    setlocale(LC_ALL, "ru");
    double a, b, c, d;
    double u;
    double y_0;
    int num_steps;
    int model_choice;

    // Ввод параметров пользователем
    cout << "Введите коэффициент а: ";
    cin >> a;
    cout << "Введите коэффициент b: ";
    cin >> b;
    cout << "Введите коэффициент c (только для нелинейной модели): ";
    cin >> c;
    cout << "Введите коэффициент d (только для нелинейной модели): ";
    cin >> d;

    cout << "Введите подаваемое тепло u: ";
    cin >> u;

    cout << "Введите начальную температуру y_0: ";
    cin >> y_0;

    cout << "Введите количество шагов для моделирования: ";
    cin >> num_steps;

    cout << "Выберите модель (1 – Линейная, 2 – Нелинейная): ";
    cin >> model_choice;

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
            cout << "Неверный выбор модели!" << endl;
            return -1;
        }
    }

    // Вывод результатов
    cout << "\nТемпература с течением времени:\n";
    for (int t = 0; t < num_steps; ++t) {
        cout << "Шаг " << t + 1 << ": " << temperatures[t] << " C" << endl;
    }

    return 0;
}
