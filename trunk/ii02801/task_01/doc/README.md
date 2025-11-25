<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Артыш Е.А.</p>
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

const double a = 0.9;
const double b = 0.1;
const double c = 0.05;
const double d = 0.02;

const double y0_value = 20.0;  
const double C = 1.0;

std::vector<double> simulateLinear(int steps, double y_init, const std::vector<double>& u) {
    std::vector<double> y(steps);
    y[0] = y_init;

    for (int t = 1; t < steps; ++t) {
        y[t] = a * y[t - 1] + b * u[t - 1];
    }

    return y;
}

std::vector<double> simulateNonlinear(int steps, double y_init, const std::vector<double>& u) {
    if (steps == 0) {
        // No steps, return empty vector
        return std::vector<double>();
    } else if (steps == 1) {
        // Only initial value
        return std::vector<double>(1, y_init);
    } else if (steps == 2) {
        // Initial value and first computed value
        std::vector<double> y(2);
        y[0] = y_init;
        y[1] = a * y[0] + b * u[0];
        return y;
    }
    std::vector<double> y(steps);
    y[0] = y_init;
    y[1] = a * y[0] + b * u[0];
    for (int t = 2; t < steps; ++t) {
        y[t] = a * y[t - 1] - b * std::pow(y[t - 2], 2) + c * u[t - 1] + d * std::sin(u[t - 2]);
    }

    return y;
}


int main() {
    int steps = 20;
    double y_init = 25.0;

    std::vector<double> u(steps, 5.0);

    auto y_linear = simulateLinear(steps, y_init, u);
    auto y_nonlinear = simulateNonlinear(steps, y_init, u);

    std::cout << "Time\tLinear\tNonlinear\n";
    for (int t = 0; t < steps; ++t) {
        std::cout << t << "\t" << y_linear[t] << "\t" << y_nonlinear[t] << "\n";
    }

    return 0;
}

```
Вывод программы:
```
Time	Linear	Nonlinear
0	25	25
1	23	23
2	21.2	-41.5692
3	19.58	-90.0814
4	18.122	-253.642
5	16.8098	-1039.51
6	15.6288	-7368.76
7	14.5659	-114691
8	13.6093	-5.53309e+06
9	12.7484	-1.32037e+09
10	11.9736	-3.0627e+12
11	11.2762	-1.74341e+17
12	10.6486	-9.38012e+23
13	10.0837	-3.03947e+33
14	9.57536	-8.79866e+46
15	9.11782	-9.23839e+65
16	8.70604	-7.74164e+92
17	8.33544	-8.53479e+130
18	8.00189	-5.9933e+184
19	7.7017	-7.28426e+260


```
