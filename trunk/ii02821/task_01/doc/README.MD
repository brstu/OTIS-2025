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
<p align="right">Манцевич Р.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
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

Task is to write program (**C++**), which simulates this object temperature.

<hr>

# Выполнение задания #

Код программы:
```
#include <iostream>
#include <cmath>
using namespace std;

double nextLinear(double a, double b, double u, double y) {
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps) {
    cout << "Линейная модель" << endl;
    double y = 0.0;
    for (int i = 0; i < steps; i++) {
        cout << "τ=" << i << ": y=" << y << endl;
        y = nextLinear(a, b, u, y);
    }
}

double nextNonlinear(double a, double b, double c, double d, 
                    double u, double u_prev, double y, double y_prev) {
    return a * y - b * (y_prev * y_prev) + c * u + d * sin(u_prev);
}

void simulateNonlinear(double a, double b, double c, double d, double u, int steps) {
    cout << "Нелинейная модель" << endl;
    double y = 0.0, y_prev = 0.0;
    double u_prev = 0.0;
    
    for (int i = 0; i < steps; i++) {
        cout << "τ=" << i << ": y=" << y << endl;
            double y_next = nextNonlinear(a, b, c, d, u, u_prev, y, y_prev);
            y_prev = y;
            y = y_next;
        
        u_prev = u; 
    }
}

int main() {
    double a1 = 0.3, b1 = 0.3, u1 = 0.9;
    int n1 = 10;
    simulateLinear(a1, b1, u1, n1);
    cout << endl;

    double a2 = 0.1, b2 = 0.2, c2 = 0.4, d2 = 0.2, u2 = 0.8;
    int n2 = 10;
    simulateNonlinear(a2, b2, c2, d2, u2, n2);

    return 0;
}
```     
```
Линейная модель
0
0.27
0.351
0.3753
0.38259
0.384777
0.385433
0.38563
0.385689
0.385707
Нелинейная модель
0
0.568294
0.625124
0.461392
0.431455
0.46404
0.472645
0.467669
0.46556
0.466284
```