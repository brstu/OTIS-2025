
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

<p align="right">Клименко М.С.</p>

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
#include  <iostream>
#include  <cmath>

int  main()
{
	double y = 0;
	double u = 0;
	double u_prev = 0;
	double a = 0;
	double b = 0;
	double c = 0;
	double d = 0;

	int  n = 0;

	std::cout << "Enter input temperature (y): ";
	std::cin >> y;
	std::cout << "Enter input warm (u): ";
	std::cin >> u;
	double y0 = 0;
	double y1 = y;
	double y2 = 0;
	std::cout << "Enter constants a, b, c, d: ";
	std::cin >> a >> b >> c >> d;

	std::cout << "Enter an amount of steps (n): ";
	std::cin >> n;

	for (int i = 1; i <= n; i++)
	{
		y = a * y + b * u;
		y2 = a * y1 - b * pow(y0, 2) + c * u + d * sin(u_prev);
		y0 = y1;
		y1 = y2;
		u_prev = u;
		std::cout << "Step " << i
			<< ", temp of linear function = "<< y
			<< ", temp of nonlinear function = " << y2 << std::endl;
	}

	return  0;
}
```

Вывод программы:

```

Enter input temperature (y): 1.523
Enter input warm (u): 52.14
Enter constants a, b, c, d: 0.1
0.2
0.01
0.5
Enter an amount of steps (n): 9
Step 1, temp of linear function = 10.5803, temp of nonlinear function = 1.15082
Step 2, temp of linear function = 11.486, temp of nonlinear function = 0.649691
Step 3, temp of linear function = 11.5766, temp of nonlinear function = 0.798609
Step 4, temp of linear function = 11.5857, temp of nonlinear function = 0.993956
Step 5, temp of linear function = 11.5866, temp of nonlinear function = 0.970355
Step 6, temp of linear function = 11.5867, temp of nonlinear function = 0.897961
Step 7, temp of linear function = 11.5867, temp of nonlinear function = 0.899993
Step 8, temp of linear function = 11.5867, temp of nonlinear function = 0.927248
Step 9, temp of linear function = 11.5867, temp of nonlinear function = 0.929242

```
