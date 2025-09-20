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
<p align="right">Группы ИИ-27</p>
<p align="right">Гинь Н.А.</p>
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

Task is to write program (**Julia**), which simulates this object temperature.

<hr>

# Выполнение задания #

Код программы:
```
#include  <iostream>
#include <cmath>

int  main()
{
	double y;
	double y_prev;
	double y_next;
	double u;
	double a;
	double b;
	double c;
	double d;
	int n;
	std::cout << "Enter y(starting temperature) and u(input warm at every step) values: ";
	std::cin >> y >> u;
	std::cout << "Enter a, b, c, d(constants) values: ";
	std::cin >> a >> b >> c >> d;
	std::cout << "Enter number of steps n: ";
	std::cin >> n;
	y_prev = y;
	for (int i = 0; i < n; i++)
	{
		y = a * y + b * u;
		std::cout << "Result of the " << i + 1 << " step of linear model: " << y << '\n';
	}
	y = y_prev;
	y_prev = 0;
	for (int i = 0; i < n; i++)
	{
		std::cout << "Result of the " << i + 1 << " step of non-linear model: " << y << '\n';
		y_next = a * y - b * y_prev * y_prev + c * u + d * sin(u);
		y_prev = y;
		y = y_next;
	}
	return 0;
}
```     
```
Enter y(starting temperature) and u(input warm at every step) values: 1 10
Enter a, b, c, d(constants) values: 0.1 0.01 0.2 0.05
Enter number of steps n: 7
Result of the 1 step of linear model: 0.2
Result of the 2 step of linear model: 0.12
Result of the 3 step of linear model: 0.112
Result of the 4 step of linear model: 0.1112
Result of the 5 step of linear model: 0.11112
Result of the 6 step of linear model: 0.111112
Result of the 7 step of linear model: 0.111111
Result of the 1 step of non-linear model: 1
Result of the 2 step of non-linear model: 2.0728
Result of the 3 step of non-linear model: 2.17008
Result of the 4 step of non-linear model: 2.14684
Result of the 5 step of non-linear model: 2.14039
Result of the 6 step of non-linear model: 2.14075
Result of the 7 step of non-linear model: 2.14106
```