<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">по дисциплине "Общая теория интеллектуальных систем"</p>
<p align="center">Тема: "Моделирование температуры объекта"</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Олексюк И.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
3. Выполнить рецензирование (review, checklist) запросов других студентов (минимум 2-е рецензии).
4. Отразить выполнение работы в файлe readme.md в соответствующей строке.

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input heat; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

# Выполнение задания #

## Код программы ##

```cpp
#include <iostream>
#include <cmath>

int main()
{
    double u_current;
    double u_prev;
    double y;
    double a;
    double b;
    double c;
    double d;
    int count_steps;

    std::cout << "Enter initial temperature y: ";
    if (!(std::cin >> y)) {
        std::cerr << "Error: Invalid input for y" << std::endl;
        return 1;
    }

    std::cout << "Enter initial heat u: ";
    if (!(std::cin >> u_current)) {
        std::cerr << "Error: Invalid input for u" << std::endl;
        return 1;
    }

    u_prev = u_current;

    std::cout << "Enter constants a, b, c, d: ";
    if (!(std::cin >> a >> b >> c >> d)) {
        std::cerr << "Error: Invalid input for constants" << std::endl;
        return 1;
    }

    std::cout << "Enter number of steps: ";
    if (!(std::cin >> count_steps) || count_steps <= 0) {
        std::cerr << "Error: Invalid number of steps" << std::endl;
        return 1;
    }

    double y_linear = y;
    double y_nonlinear_prev = y;
    double y_nonlinear = y;

    std::cout << "\nSimulation results:" << std::endl;
    for (int i = 0; i < count_steps; i++)
    {
        double y_linear_next = a * y_linear + b * u_current;
        std::cout << "Step:  " << i + 1 << " linear model" << std::endl;
        std::cout << " y = " << y_linear_next << std::endl;

        u_prev = u_current;
        y_linear = y_linear_next;
    }
    for (int i = 0; i < count_steps; i++)
    {
        double y_nonlinear_next = a * y_nonlinear - b * y_nonlinear_prev * y_nonlinear_prev
            + c * u_current + d * std::sin(u_prev);
        std::cout << "Step: " << i + 1 << " nonlinear model" << std::endl;
        std::cout << " y = " << y_nonlinear_next << std::endl;
        y_nonlinear_prev = y_nonlinear;
        y_nonlinear = y_nonlinear_next;
        u_prev = u_current;
    }

    return 0;
}

```
Вывод программы:
```
Enter initial temperature y: 4.33
Enter initial heat u: 2.3
Enter constants a, b, c, d: 1.5 0.88 0.76 2
Enter number of steps: 4
Step:  1 linear model
 y = 8.519
Step:  2 linear model
 y = 14.8025
Step:  3 linear model
 y = 24.2278
Step:  4 linear model
 y = 38.3656
Step: 1 nonlinear model
 y = -6.76462
Step: 2 nonlinear model
 y = -23.4066
Step: 3 nonlinear model
 y = -72.1393
Step: 4 nonlinear model
 y = -587.092
```