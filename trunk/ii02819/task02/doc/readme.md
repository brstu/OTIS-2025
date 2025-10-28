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
