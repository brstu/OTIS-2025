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
<p align="right">Цибульскас В.С.</p>
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

double linear(double y, double u, double a, double b);
double non_linear(double y, double u, double a, double b, double c, double d);

int main()
{
    double u;
    double y;
    std::cout << "Enter u(input warm) and y(input temperature): " << std::endl;
    std::cin >> u >> y;

    double a;
    double b; 
    double c;
    double d;
    std::cout << "Enter a,b,c,d(some constants): " << std::endl;
    std::cin >> a >> b >> c >> d;

    int count;
    std::cout << "Enter the number of steps: " << std::endl;
    std::cin >> count;

    double yl = y;
    double ynl = y;
    for (int i = 0; i < count; i++)
    {
        yl = linear(yl, u, a, b);
        ynl = non_linear(ynl, u, a, b, c, d);

        std::cout << "Result of the " << i + 1 << " step of linear model: " << yl << ";\n";
        std::cout << "Result of the " << i + 1 << " step of non-linear model: " << ynl << ";\n";
    }

    return 0;
}

double linear(double y, double u, double a, double b)
{
    return a * y + b * u;
}

double non_linear(double y, double u, double a, double b, double c, double d)
{
    return a * y - b * y * y + c * u + d * std::sin(u);
}
```
Вывод программы:
```
Enter u(input warm) and y(input temperature): 
2 2
Enter a,b,c,d(some constants): 
1.1 0.5 0.88 1.4
Enter the number of steps: 
8
Result of the 1 step of linear model: 3.2;
Result of the 1 step of non-linear model: 3.23302;
Result of the 2 step of linear model: 4.52;
Result of the 2 step of non-linear model: 1.36314;
Result of the 3 step of linear model: 5.972;
Result of the 3 step of non-linear model: 3.6034;
Result of the 4 step of linear model: 7.5692;
Result of the 4 step of non-linear model: 0.504521;
Result of the 5 step of linear model: 9.32612;
Result of the 5 step of non-linear model: 3.46072;
Result of the 6 step of linear model: 11.2587;
Result of the 6 step of non-linear model: 0.85152;
Result of the 7 step of linear model: 13.3846;
Result of the 7 step of non-linear model: 3.60715;
Result of the 8 step of linear model: 15.7231;
Result of the 8 step of non-linear model: 0.495128;
```
## Рецензирование запросов других студентов ##
![Рецензия работы пользователя JohnyDepp228:](https://ibb.co/C5qn0wCt)

![Рецензия работы пользователя humoristoff :](https://ibb.co/1tzGXp7h)