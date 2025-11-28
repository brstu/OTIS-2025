<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учебное заведение</p>
<p align="center">Брестский государственный технический университет</p>
<p align="center">Кафедра информационных и интеллектуальных технологий</p>
<div style="margin-bottom: 8em;"></div>
<p align="center">Лабораторная работа №1</p>
<p align="center">Дисциплина: «Общая теория интеллектуальных систем»</p>
<p align="center">Тема: «Моделирование температурного поведения объекта»</p>
<div style="margin-bottom: 8em;"></div>
<p align="right">Автор работы:</p>
<p align="right">Студент второго курса</p>
<p align="right">Группа ИИ-27/24</p>
<p align="right">Козел А. В.</p>
<p align="right">Преподаватель:</p>
<p align="right">Иванюк Д. С.</p>
<div style="margin-bottom: 8em;"></div>
<p align="center">Брест, 2025</p>

---

# Задание #
1. Подготовить отчёт по лабораторной работе №1 в формате Markdown (README.md) и разместить его в каталоге: trunk\ii02709\task_01\doc.

2. Исходный код программы необходимо сохранить в директории: trunk\ii02709\task_01\src.

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau}^2+cu_{\tau}+d\sin(u_{\tau})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

---

# Код программы #

#include <iostream>
#include <vector>
#include <cmath>

const long double a = 0.9;
const long double b = 0.5;
const long double c1 = 0.1;
const long double c2 = 0.05;

int main() {
    int steps = 20;
    long double y_linear = 1.5;
    long double y_nonlinear = 1.5;
    long double u = 2.0;

    std::vector<long double> linear_values;
    std::vector<long double> nonlinear_values;

    linear_values.reserve(steps);
    nonlinear_values.reserve(steps);

    for (int t = 0; t < steps; ++t) {
        long double next_linear = a * y_linear + b * u;
        long double next_nonlinear = a * y_nonlinear - b * y_nonlinear * y_nonlinear + c1 * u + c2 * std::sinh(u);
        linear_values.push_back(next_linear);
        nonlinear_values.push_back(next_nonlinear);

        y_linear = next_linear;
        y_nonlinear = next_nonlinear;
    }

    std::cout.precision(18);
    std::cout << "Step\tLinear\t\t\tNonLinear\n";
    for (int t = 0; t < steps; ++t) {
        std::cout << t << "\t"
                  << linear_values[t] << "\t"
                  << nonlinear_values[t] << "\n";
    }

    return 0;
}

---

Вывод программы: 

Step    Linear                  NonLinear
0       2.35000000000000003     0.606343020392350993
1       3.11500000000000008     0.743225809556207381
2       3.80350000000000014     0.774053946997697698
3       4.42315000000000021     0.778411816258921606
4       4.98083500000000029     0.778951177179623857
5       5.48275150000000037     0.779016611639251569
6       5.93447635000000046     0.779024530262727137
7       6.34102871500000054     0.779025488253274066
8       6.70692584350000063     0.779025604146171611
9       7.03623325915000071     0.779025618166251591
10      7.3326099332350008      0.779025619862322198
11      7.59934893991150088     0.77902562006750329
12      7.83941404592035096     0.779025620092324946
13      8.05547264132831604     0.77902562009532773
14      8.24992537719548462     0.77902562009569099
15      8.42493283947593634     0.779025620095734935
16      8.58243955552834289     0.779025620095740251
17      8.72419559997550879     0.779025620095740894
18      8.85177603997795811     0.779025620095740972
19      8.96659843598016249     0.779025620095740982