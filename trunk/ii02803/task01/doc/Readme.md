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
<<<<<<< HEAD
=======
<p align="right">Студент 2 курса</p>
>>>>>>> b47b9bdce0b40ba7de3b2e571827303ebe495122
=======
<p align="right">Студентка 2 курса</p>
>>>>>>> origin/task1
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

vector<double> fun2(double a, double b, double c, double d, double e, double f, double g) {
    int n = 5;
    vector<double> u(n + 1);
    u[0] = 1.0;
    u[1] = 1.0;
    u[2] = 1.0;
    u[3] = 1.0;
    u[4] = 1.0;
    u[5] = 0.0;
    
    double y0 = 20.0;
    double y1 = 20.5;
    
    vector<double> y(n + 1);
    y[0] = y0;
    y[1] = y1;

    for (int t = 1; t < n; t++) {
        double current_y = y[t];
        double previous_y = y[t - 1];
        double current_u = u[t];
        double previous_u = u[t - 1];
        double squared_previous_y = previous_y * previous_y;
        double squared_current_u = current_u * current_u;
        double sin_previous_u = sin(previous_u);
        double cos_current_y = cos(current_y);
        
        y[t + 1] = a * current_y + 
                   b * squared_previous_y + 
                   c * current_u + 
                   d * sin_previous_u + 
                   e * squared_current_u + 
                   f * cos_current_y + 
                   g;
    }
    return y;
}

int main() {
    int n;
    double a_lin;
    double b_lin;
    double a_nlin;
    double b_nlin;
    double c_nlin;
    double d_nlin;
    double e_nlin;
    double f_nlin;
    double g_nlin;

    cout << "Number of steps n: ";
    cin >> n;

    cout << "Parameters for linear model (a, b): ";
    cin >> a_lin;
    cin >> b_lin;

    cout << "Parameters for nonlinear model (a, b, c, d, e, f, g): ";
    cin >> a_nlin;
    cin >> b_nlin;
    cin >> c_nlin;
    cin >> d_nlin;
    cin >> e_nlin;
    cin >> f_nlin;
    cin >> g_nlin;

    vector<double> u(n + 1);
    cout << "Enter " << n << " values of the input signal u (u[0] to u[" << n-1 << "]):\n";
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }
    u[n] = 0.0;

    double y0;
    double y1;
    cout << "Initial conditions y0 and y1: ";
    cin >> y0;
    cin >> y1;

    vector<double> yLinear = fun1(n, a_lin, b_lin, u, y0);
    vector<double> yNonlinear = fun2(a_nlin, b_nlin, c_nlin, d_nlin, e_nlin, f_nlin, g_nlin);

    cout << "Time\tLinear Model\tNonlinear Model\n";
    cout << fixed;
    cout.precision(4);
    for (int t = 0; t <= n; t++) {
        cout << t << "\t" << yLinear[t] << "\t\t" << yNonlinear[t] << "\n";
    }

    return 0;
}

Number of steps n: 5
Parameters for linear model (a, b): 0.8 0.2
Parameters for nonlinear model (a, b, c, d, e, f, g): 0.5 0.1 0.3 0.05 0.01 0.02 0.1
Enter 5 values of the input signal u (u[0] to u[4]):
1 1 1 1 1
Initial conditions y0 and y1: 20 20.5

Time    Linear Model    Nonlinear Model
0       20.0000         20.0000
1       16.2000         20.5000
2       13.1600         25.2918
3       10.7280         30.5498
4       8.7824          36.2839
5       7.2259          42.5044

