<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Маковей Е.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.
---
# Код программы: #
```C++
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

```     
```
Желаемое начальное значение: 0.1
0
0
0
0.0921037
0.123099
0.112206
0.0891094
0.08883
0.102193
0.106844
0.101074
0.0963006
0.0981692
0.101519
0.101602
0.099696
0.0990021
0.0998769
0.10057
0.1003
0.0998062
0.0997951
0.100076
0.100176
0.100046
0.0999437
0.0999829
0.100054
0.100055
0.100013
0.0999969
0.100015
0.100029
0.100022
0.100011
0.10001
0.100015
0.100016
0.100013
0.10001
0.10001
0.10001
0.100009
0.100008
0.100006
0.100006
0.100005
0.100004
0.100003
0.100002
0.100002
0.100001
0.1
```
![График](./unliner.png)
