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
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Жукович Е.Д.</p>
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



const std::vector<double> params{ 0.8, 0.6, 0.4, 2.2 };
const double heat_input = 0.8;

std::vector<double> linearSim(int n, double start_temp) {
    std::vector<double> data(n);
    data[0] = start_temp;

    for (int i = 1; i < n; i++) {
        data[i] = params[0] * data[i - 1] + params[1] * heat_input;
    }
    return data;
}

std::vector<double> nonlinearSim(int n, double start_temp) {
    std::vector<double> data(n);
    data[0] = start_temp;

    if (n > 1) {
        data[1] = params[0] * data[0] + params[2] * heat_input + params[3] * sin(heat_input);
    }

    for (int i = 2; i < n; i++) {
        data[i] = params[0] * data[i - 1] - params[1] * data[i - 2] * data[i - 2]
            + params[2] * heat_input + params[3] * sin(heat_input);
    }
    return data;
}

int main() {
    double start_temp;
    int steps;

    std::cout << "Enter starting temperature: ";
    std::cin >> start_temp;

    std::cout << "Enter number of steps: ";
    std::cin >> steps;

    while (steps < 1) {
        std::cout << "Steps must be 1 or more: ";
        std::cin >> steps;
    }

    std::vector<double> linear_data = linearSim(steps, start_temp);
    std::vector<double> nonlinear_data = nonlinearSim(steps, start_temp);

    std::cout << "\nLinear Model Results:" << std::endl;
    for (int i = 0; i < steps; i++) {
        std::cout << "Step " << i << ": " << linear_data[i] << std::endl;
    }

    std::cout << "\nNonlinear Model Results:" << std::endl;
    for (int i = 0; i < steps; i++) {
        std::cout << "Step " << i << ": " << nonlinear_data[i] << std::endl;
    }

    return 0;
}
```     
Enter starting temperature: 4
Enter number of steps: 10

Linear Model Results:
Step 0: 4
Step 1: 3.68
Step 2: 3.424
Step 3: 3.2192
Step 4: 3.05536
Step 5: 2.92429
Step 6: 2.81943
Step 7: 2.73554
Step 8: 2.66844
Step 9: 2.61475

Nonlinear Model Results:
Step 0: 4
Step 1: 5.09818
Step 2: -3.62327
Step 3: -16.5953
Step 4: -19.2549
Step 5: -178.748
Step 6: -363.552
Step 7: -19459.6
Step 8: -94867.7
Step 9: -2.2728e+08

