<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Вабищевич И.В</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02102**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation, we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

<hr>

# Выполнение задания #

Код программы:
```C++
#include <iostream> 
#include <vector>
#include <cmath>

using namespace std;

vector<double> fun1(int n, double a, double b, const vector<double>& u, double y0) {
    vector<double> y(n + 1);
    y[0] = y0;
    for (int t = 0; t < n; t++) {
        y[t + 1] = a * y[t] + b * u[t];
    }
    return y;
}

vector<double> fun2(int n, double a, double b, double c, double d,
                                 const vector<double>& u, double y0, double y1) {
    vector<double> y(n + 1);
    y[0] = y0;
    y[1] = y1;

    for (int t = 1; t < n; t++) {
        y[t + 1] = a * y[t] - b * (y[t - 1] * y[t - 1]) + c * u[t] + d * sin(u[t - 1]);
    }
    return y;
}

int main() {
    int n; 
    double a, b, c, d;

    cout << "Number of steps n: ";
    cin >> n;

    cout << "a, b, c, d: ";
    cin >> a >> b >> c >> d;

    vector<double> u(n);
    cout << "Enter " << n << " values of the input signal u:\n";
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }

    double y0, y1;
    cout << "Initial conditions y0 and y1: ";
    cin >> y0 >> y1;

    auto yLinear = fun1(n, a, b, u, y0);
    auto yNonlinear = fun2(n, a, b, c, d, u, y0, y1);

    cout << "Time\tLinear Model\tNonlinear Model\n";
    for (int t = 0; t <= n; t++) {
        cout << t << "\t" << yLinear[t] << "\t\t" << yNonlinear[t] << "\n";
    }

    return 0;
}

Enter number of steps n: 5
Enter coefficients a, b, c, d: 0.8 0.2 0.3 0.1
Enter 5 values of the input signal u:
1 1 1 1 1
Enter initial conditions y0 and y1: 20 20.5

Time    Linear Model    Nonlinear Model
0       20              20
1       16.2            20.5
2       13.16           -63.216
3       10.728          -134.24
4       8.7824          -906.2
5       7.2259          -4330.6

