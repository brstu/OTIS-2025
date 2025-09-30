#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    double u, y, a, b, c, d;
    int count_steps;

    cout << "Введите u(входящую теплоту) и y(входящую температуру): " << endl;
    cin >> u >> y;
    cout << "Введите константы a, b, c, d: " << endl;
    cin >> a >> b >> c >> d;
    cout << "Введите количество шагов: " << endl;
    cin >> count_steps;
    double yl = y, ynl = y;
    for (int i = 0; i < count_steps; i++)
    {
        yl = a * yl + b * u;
        ynl = a * ynl - b * ynl * ynl + c * u + d * sin(u);
        cout << "Результат " << i + 1 << " шага линейной функции: " << yl << ";\n";
        cout << "Результат " << i + 1 << " шага НЕлинейной функции: " << ynl << ";\n";
    }
    return 0;
}