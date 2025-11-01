<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Лыщенко К.В.</p>
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

// параметры нелинейной модели
struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

// линейная модель
double Linear(double a, double b, double u, double y) {
    return a * y + b * u;
}

// симуляция линейной модели
void simulateLinear(double a, double b, double u, int steps) {
    std::cout << "Linear model" << std::endl;
    double y = 0.0;
    for (int i = 0; i < steps; ++i) {
        std::cout << "Step " << i << ": " << y << std::endl;
        y = Linear(a, b, u, y);
    }
    std::cout << std::endl;
}

// нелинейная модель
double Nonlinear(const NonlinearParams& p, double u, double uPrev, double y, double yPrev) {
    return p.a * y - p.b * (yPrev * yPrev) + p.c * u + p.d * sin(uPrev);
}

// симуляция нелинейной модели
void simulateNonlinear(const NonlinearParams& p, double u, int steps) {
    std::cout << "Nonlinear model" << std::endl;
    double y = 0.0;
    double yPrev = 0.0;
    double uPrev = 0.0;
    for (int i = 0; i < steps; ++i) {
        std::cout << "Step " << i << ": " << y << std::endl;
        double yNext = Nonlinear(p, u, uPrev, y, yPrev);
        yPrev = y;
        uPrev = u;
        y = yNext;
    }
    std::cout << std::endl;
}

int main() {
    // параметры линейной модели
    double a1 = 0.1;
    double b1 = 0.3;
    double u1 = 0.5;
    int n1 = 10;

    simulateLinear(a1, b1, u1, n1);

    // параметры нелинейной модели
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    double u2 = 0.15;
    int n2 = 10;

    simulateNonlinear(p, u2, n2);

    return 0;
}
```     
```
Linear model
Step 0: 0
Step 1: 0.15
Step 2: 0.165
Step 3: 0.1665
Step 4: 0.16665
Step 5: 0.166665
Step 6: 0.166666
Step 7: 0.166667
Step 8: 0.166667
Step 9: 0.166667

Nonlinear model
Step 0: 0
Step 1: 0.219391
Step 2: 0.189501
Step 3: 0.125258
Step 4: 0.0912882
Step 5: 0.0857081
Step 6: 0.0884224
Step 7: 0.0912114
Step 8: 0.0927382
Step 9: 0.0933562
```