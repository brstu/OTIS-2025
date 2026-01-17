<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделированиe температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Сыч А.Д.</p>
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
#include <vector>
#include <format>
#include <iomanip>

struct ModelParameters {
    double a1;
    double b;
    double c;
    double d;
};

double computeLinear(double y1, double u1, double a1, double b1) {
    return a1 * y1 + b1 * u1;
}

double computeNonLinear(double y, double& prev_y, double u, const ModelParameters& params) {
    double result = params.a1 * y - params.b * prev_y * prev_y + params.c * u + params.d * std::sin(u);
    prev_y = y;
    return result;
}

void simulateModel(int steps, double u, const ModelParameters& params, double init_y_linear, double init_y_nonlinear, double init_prev_y) {

    std::cout << "\nSimulation Results:\n";
    std::cout << std::string(50, '-') << std::endl;

    double y_linear = init_y_linear;
    double y_nonlinear = init_y_nonlinear;
    double prev_y_nonlinear = init_prev_y;

    for (int step = 0; step < steps; ++step) {
        y_linear = computeLinear(y_linear, u, params.a1, params.b);
        y_nonlinear = computeNonLinear(y_nonlinear, prev_y_nonlinear, u, params);

        std::cout << std::format("Step {:2}: Linear = {:10.4f} | Non-linear = {:10.4f}", step, y_linear, y_nonlinear) << std::endl;
    }
}

int main() {
    double y_current;
    double y_previous;
    double u_input;
    std::cout << "Enter initial conditions (Y_{n-1}, Y_n, U): ";
    std::cin >> y_previous >> y_current >> u_input;

    ModelParameters params;
    std::cout << "Enter model parameters (A, B, C, D): ";
    std::cin >> params.a1 >> params.b >> params.c >> params.d;

    int num_steps;
    std::cout << "Enter number of simulation steps: ";
    std::cin >> num_steps;

    simulateModel(num_steps, u_input, params, y_current, y_current, y_previous);

    return 0;
}
```
Вывод программы:
```
Enter Yn-1, Y and U values:
1 2 3
Enter A, B, C, D values:
1 2 3 2
Enter number of steps N: 5
The 0st step of linear model - 8
The 1st step of linear model - 14
The 2st step of linear model - 20
The 3st step of linear model - 26
The 4st step of linear model - 32
The 0st step of nonlinear model - 3.28224
The 1st step of nonlinear model - -8.98172
The 2st step of nonlinear model - -161.042
The 3st step of nonlinear model - -52020.8
The 4st step of nonlinear model - -5.41239e+09
```
## Рецензирование запросов других студентов ##
![Рецензия работы пользователя threenebula23:](https://i.ibb.co/mF8Trkgx/img1.png)

![Комментарий к коду пользователя oniisssss:](https://i.ibb.co/pvTVwcQ6/img2.png)
