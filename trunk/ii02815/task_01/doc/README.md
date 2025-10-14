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
#include <limits>
#include <string>

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

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool readDouble(const std::string& text, double& value) {
    std::cout << text;
    std::cin >> value;
    while (std::cin.fail()) {
        clearInput();
        std::cout << "Invalid input. Please enter a numeric value.\n" << text;
        std::cin >> value;
    }
    return true;
}

bool readPositiveInt(const std::string& text, int& value) {
    std::cout << text;
    std::cin >> value;
    while (std::cin.fail() || value <= 0) {
        clearInput();
        std::cout << "Invalid input. Please enter a positive integer.\n" << text;
        std::cin >> value;
    }
    return true;
}

int main() {
    double a;
    double b;
    double c;
    double d;
    double y0;
    double u0;
    int n;

    readDouble("Enter constant a: ", a);
    readDouble("Enter constant b: ", b);
    readDouble("Enter constant c: ", c);
    readDouble("Enter constant d: ", d);
    readDouble("Enter initial output y0: ", y0);
    readDouble("Enter initial input u0: ", u0);
    readPositiveInt("Enter number of steps (n): ", n);

    ModelParameters params{a, b, c, d};

    double y_linear_current = y0;
    double y_nonlinear_current = y0;
    double y_nonlinear_previous = y0;
    double u_previous = u0;
    double u_current;

    std::cout << "Steps\tLinear model\tNonlinear model\n";

    for (int step = 1; step <= n; ++step) {
        readDouble("Enter input u for step " + std::to_string(step) + ": ", u_current);

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
Enter constant a: 0.3
Enter constant b: 0.8
Enter constant c: 1.3
Enter constant d: 1.6
Enter initial output y0: 1
Enter initial input u0: 1
Enter number of steps (n): 8
Steps   Linear model    Nonlinear model
Enter input u for step 1: 1
1       1.1             2.14635
Enter input u for step 2: 2
2       1.93            3.79026
Enter input u for step 3: 3
3       2.979           2.80649
Enter input u for step 4: 4
4       4.0937          -5.22512
Enter input u for step 5: 5
5       5.22811         -2.57951
Enter input u for step 6: 6
6       6.36843         -16.3496
Enter input u for step 7: 7
7       7.51053         -1.57506
Enter input u for step 8: 8
8       8.65316         -202.869
```