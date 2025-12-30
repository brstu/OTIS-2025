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
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
3. Выполнить рецензирование ([review](https://linearb.io/blog/code-review-on-github), [checklist](https://linearb.io/blog/code-review-checklist)) запросов других студентов (минимум 2-е рецензии).
4. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2023/edit/main/readme.md?#L17-L17).

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warmth; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.


## Код программы:
```C++
#include <iostream>
#include <cmath>

int main()
{
	double y;
	double y_prev;
	double y_next;
	double u;
	double u_prev;
	double a;
	double b;
	double c;
	double d;
	int n;
	std::cout << "Enter y (starting temperature) and u (input warmth at first step) values (space-separated): ";
	std::cin >> y >> u; 
	std::cout << "Enter a, b, c, d (constants) values: ";
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
	u_prev = u;
	for (int i = 0; i < n; i++)
	{
		y_next = a * y - b * y_prev * y_prev + c * u + d * sin(u_prev); // Use previous input value as per specification
		y_prev = y;
		y = y_next;
		std::cout << "Result of the " << i + 1 << " step of non-linear model: " << y << '\n';
		u_prev = u; // Update u_prev to current input value for next iteration (if u changes per step)
		std::cout << "Enter u for the " << i + 1 << " step: ";
		std::cin >> u;
	}
	return 0;
}

```

## Результат программы:
Enter y (starting temperature) and u (input warmth at first step) values (space-separated):  1 10
Enter a, b, c, d (constants) values: 0.01 0.03 0.05 0.01
Enter number of steps n: 7
Result of the 1 step of linear model: 0.31
Result of the 2 step of linear model: 0.3031
Result of the 3 step of linear model: 0.303031
Result of the 4 step of linear model: 0.30303
Result of the 5 step of linear model: 0.30303
Result of the 6 step of linear model: 0.30303
Result of the 7 step of linear model: 0.30303
Result of the 1 step of non-linear model: 1
Enter u for the 2 step: 10
Result of the 2 step of non-linear model: 0.50456
Enter u for the 3 step: 10
Result of the 3 step of non-linear model: 0.469605
Enter u for the 4 step: 10
Result of the 4 step of non-linear model: 0.491618
Enter u for the 5 step: 10
Result of the 5 step of non-linear model: 0.49286
Enter u for the 6 step: 10
Result of the 6 step of non-linear model: 0.492238
Enter u for the 7 step: 10
Result of the 7 step of non-linear model: 0.492195

