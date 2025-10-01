<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Корнелюк Я.М.</p>
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

struct ModelParameters {
    double a;
    double b;
    double c;
    double d;
};

double linearModel(double y_current, double u_current, const ModelParameters& params) {
    return params.a * y_current + params.b * u_current;
}

double nonlinearModel(double y_current, double y_previous, double u_current, double u_previous, const ModelParameters& params) {
    return params.a * y_current - params.b * y_previous * y_previous + params.c * u_current + params.d * sin(u_previous);
}

int main() {
    double a;
    double b;
    double c;
    double d;
    double y0;
    double u0;
    int n;

    std::cout << "Enter constants a, b, c, d: ";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> d;

    std::cout << "Enter initial output y0: ";
    std::cin >> y0;

    std::cout << "Enter initial input u0: ";
    std::cin >> u0;

    std::cout << "Enter number of steps (n): ";
    std::cin >> n;

    ModelParameters params{a, b, c, d};

    double y_linear_current = y0;
    double y_nonlinear_current = y0;
    double y_nonlinear_previous = y0;

    double u_previous = u0;
    double u_current;

    std::cout << "Steps\tLinear model\tNonlinear model\n";

    for (int step = 1; step <= n; ++step) {
        std::cout << "Enter input u for step " << step << ": ";
        std::cin >> u_current;
        double linear_result = linearModel(y_linear_current, u_current, params);
        double nonlinear_result = nonlinearModel(y_nonlinear_current, y_nonlinear_previous, u_current, u_previous, params);
        std::cout << step << "\t" << linear_result << "\t\t" << nonlinear_result << "\n";
        y_linear_current = linear_result;
        y_nonlinear_previous = y_nonlinear_current;
        y_nonlinear_current = nonlinear_result;

        u_previous = u_current;
    }
    return 0;
}
```
Вывод программы:
```
Enter constants a, b, c, d: 0.3 0.8 1.3 1.5
Enter initial output y0: 1
Enter initial input u0: 1
Enter number of steps (n): 10
Steps   Linear model    Nonlinear model
Enter input u for step 1: 3
1       2.7             4.66221
Enter input u for step 2: 4    
2       4.01            6.01034
Enter input u for step 3: 6    
3       6.003           -8.92104
Enter input u for step 4: 2     
4       3.4009          -29.3948
Enter input u for step 5: 1     
5       1.82027         -69.8224
Enter input u for step 6: 9     
6       7.74608         -699.228
Enter input u for step 7: 5     
7       6.32382         -4102.79
Enter input u for step 8: 4
8       5.09715         -392363
Enter input u for step 9: 2
9       3.12914         -1.3584e+07
Enter input u for step 10: 3
10      3.33874         -1.23163e+11
```