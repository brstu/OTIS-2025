#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double temperature;        // y(t)
    double temperature_prev;   // y(t-1)
    double temperature_next;   // y(t+1)

    double heat;               // u(t)
    double heat_prev;          // u(t-1)

    double a, b, c, d;
    int steps;

    cout << "Введите начальную температуру и начальный нагрев: ";
    cin >> temperature >> heat;

    cout << "Введите коэффициенты a, b, c, d: ";
    cin >> a >> b >> c >> d;

    cout << "Введите количество шагов моделирования: ";
    cin >> steps;

    cout << "\nЛинейная модель:\n";

    double linear_temp = temperature;

    for (int k = 0; k < steps; k++)
    {
        linear_temp = a * linear_temp + b * heat;
        cout << "Шаг " << k + 1 << ", температура = " << linear_temp << endl;
    }

    
    cout << "\nНелинейная модель:\n";

    temperature_prev = temperature; // значение до первого шага
    heat_prev = heat;
    double current_temp = temperature;

    for (int k = 0; k < steps; k++)
    {
        temperature_next =
            a * current_temp
            - b * temperature_prev * temperature_prev
            + c * heat
            + d * sin(heat_prev);

        cout << "Шаг " << k + 1 << ", температура = " << temperature_next << endl;

        temperature_prev = current_temp;
        current_temp = temperature_next;
        heat_prev = heat;

        if (k < steps - 1)
        {
            cout << "Введите значение нагрева для следующего шага: ";
            cin >> heat;
        }
    }

    return 0;
}