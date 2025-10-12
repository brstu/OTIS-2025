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
#include <iostream>
#include <cmath>
#include <limits>
#include <string>

template <typename N>
void Number_Check(N& number, const std::string& message) {
	std::cout << message;
	while (!(std::cin >> number)) {
		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input correct number: ";
	}
}

int main()
{
	double y_lin_prev = 0;
	double y_lin_next = 0;
	double u = 0;
	double u_prev = 0;
	double a = 0;
	double b = 0;
	double c = 0;
	double d = 0;

	int n = 0;

	Number_Check(y_lin_prev, "Enter input temperature (y): ");
	Number_Check(u, "Enter input warmth (u): ");
	double y_nonlin_0 = 0;
	double y_nonlin_1 = y_lin_prev;
	double y_nonlin_2 = 0;
	Number_Check(a, "Enter constant a: ");
	Number_Check(b, "Enter constant b: ");
	Number_Check(c, "Enter constant c: ");
	Number_Check(d, "Enter constant d: ");
	Number_Check(n, "Enter an amount of steps (n): ");

	for (int i = 1; i <= n; i++)
	{
		y_lin_next = a * y_lin_prev + b * u;
		y_lin_prev = y_lin_next;
		y_nonlin_2 = a * y_nonlin_1 - b * (y_nonlin_0 * y_nonlin_0) + c * u + d * sin(u_prev);
		y_nonlin_0 = y_nonlin_1;
		y_nonlin_1 = y_nonlin_2;
		u_prev = u;
		std::cout << "Step " << i
			<< ", temp of linear function = " << y_lin_next
			<< ", temp of nonlinear function = " << y_nonlin_2 << std::endl;
	}

	return 0;
}

```
Вывод программы:
```
Enter input temperature (y): йцуыв
Input correct number: 1.25
Enter input warm (u): 2.1
Enter constant a: 0.1
Enter constant b: 0.2
Enter constant c: 0.01
Enter constant d: 0.5
Enter an amount of steps (n): 9
Step 1, temp of linear function = 0.545, temp of nonlinear function = 0.146
Step 2, temp of linear function = 0.4745, temp of nonlinear function = 0.154705
Step 3, temp of linear function = 0.46745, temp of nonlinear function = 0.463812
Step 4, temp of linear function = 0.466745, temp of nonlinear function = 0.494199
Step 5, temp of linear function = 0.466675, temp of nonlinear function = 0.459
Step 6, temp of linear function = 0.466667, temp of nonlinear function = 0.449658
Step 7, temp of linear function = 0.466667, temp of nonlinear function = 0.455434
Step 8, temp of linear function = 0.466667, temp of nonlinear function = 0.45771
Step 9, temp of linear function = 0.466667, temp of nonlinear function = 0.456892

```
