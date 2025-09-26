<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Заремская Е.П.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>


<hr>


# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
3. Выполнить рецензирование (review, checklist) запросов других студентов (минимум 2-е рецензии).
4. Отразить выполнение работы в файле readme.md в соответствующей строке.

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

# Выполнение задания #
Код программы:
```
#include <iostream>
#include <cmath>

using namespace std;

double linearModel(double y_tau, double u_tau, double a, double b) {
    return a * y_tau + b * u_tau;
}

double nonlinearModel(double y_tau, double y_tau_minus_1, double u_tau, double u_tau_minus_1, double a, double b, double c, double d) {
    return a * y_tau - b * y_tau_minus_1 * y_tau_minus_1 + c * u_tau + d * sin(u_tau_minus_1);
}

int main() {
    double a, b, c, d;
    double y0, u0;
    int n;

    cout << "Enter constants a, b, c, d: ";
    cin >> a >> b >> c >> d;
    cout << "Enter initial temperature y(0): ";
    cin >> y0;
    cout << "Enter initial input warm u(0): ";
    cin >> u0;
    cout << "Enter number of steps: ";
    cin >> n;

    double y_current = y0;
    double u_current = u0;
    double y_previous = y0;

    cout << "Step\tLinear Model\tNonlinear Model\n";
    for (int tau = 0; tau < n; tau++) {
        double linear_result = linearModel(y_current, u_current, a, b);
        double nonlinear_result = nonlinearModel(y_current, y_previous, u_current, u_current, a, b, c, d);

        cout << tau + 1 << "\t" << linear_result << "\t\t" << nonlinear_result << "\n";

        y_previous = y_current;
        y_current = linear_result;
    }

    return 0;
}
```
Вывод программы:
```
Enter constants a, b, c, d: 1 2 3 4
Enter initial temperature y(0): 3
Enter initial input warm u(0): 4
Enter number of steps: 3
Step    Linear Model    Nonlinear Model
1       11              -6.02721
2       19              1.97279
3       27              -214.027
```