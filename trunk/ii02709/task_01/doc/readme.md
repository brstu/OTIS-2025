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
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

---

# Код программы #

#include <iostream>
#include <cmath>

const double a = 0.9;
const double b = 0.5;
const double c1 = 0.1;
const double c2 = 0.05;

int main() {
    int steps = 20;
    double y_linear = 20.0;
    double y_nonlinear = 20.0;
    double u = 5.0;

    std::cout << "Step\tLinear Model\tNonlinear Model\n";

    for (int t = 0; t < steps; ++t) {
        double next_linear = a * y_linear + b * u;
        double next_nonlinear = a * y_nonlinear + b * u + c1 * u * sin(u) + c2 * u * cos(u);

        std::cout << t << "\t" << next_linear << "\t\t" << next_nonlinear << "\n";

        y_linear = next_linear;
        y_nonlinear = next_nonlinear;
    }

    return 0;
}

---

Вывод программы: 

Step    Linear Model    Nonlinear Model
0   22.5        23.9589
1   23.25       25.0171
2   23.925      26.0753
3   24.5325     27.1335
4   25.0793     28.1917
5   25.5714     29.2499
6   26.0143     30.3081
7   26.4129     31.3663
8   26.7716     32.4245
9   27.0944     33.4827
10  27.385      34.5409
11  27.6465     35.5991
12  27.8818     36.6573
13  28.0936     37.7155
14  28.2843     38.7737
15  28.456      39.8319
16  28.6104     40.8901
17  28.7494     41.9483
18  28.8745     43.0065
19  28.987      44.0647