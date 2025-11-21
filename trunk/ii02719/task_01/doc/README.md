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
<p align="right">Титунин А.А.</p>
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

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

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
	setlocale(LC_ALL, "Russian");

	const int steps = 10;
	double y[steps];
	double u[steps];
	double a;
	double b;
	double c;
	double d;

	std::cout << "Рассчет по линейной модели\n";
	std::cout << "Введите коэффициент a: ";
	std::cin >> a;
	std::cout << "Введите коэффициент b: ";
	std::cin >> b;
	std::cout << "Введите начальную температуру объекта y(0): ";
	std::cin >> y[0];
	std::cout << "Введите начальную температуру объекта u(0): ";
	std::cin >> u[0];

	for (int i = 1; i < steps; i++) 
	{
		y[i] = a * y[i - 1] + b * u[i - 1];
		u[i] = u[i - 1] * 0.8; //Коэффициент понижения температуры объекта
		std::cout << "y[" << i << "] = " << y[i] << std::endl;
	}
	
	std::cout << "Рассчет по нелинейной модели\n";
	std::cout << "Введите коэффициент a: ";
	std::cin >> a;
	std::cout << "Введите коэффициент b: ";
	std::cin >> b;
	std::cout << "Введите коэффициент c: ";
	std::cin >> c;
	std::cout << "Введите коэффициент d: ";
	std::cin >> d;
	std::cout << "Введите начальную температуру объекта y(0): ";
	std::cin >> y[0];
	std::cout << "Введите следующую температуру объекта y(1): ";
	std::cin >> y[1];
	std::cout << "Введите начальную температуру объекта u: ";
	std::cin >> u[0];
	u[1] = u[0] * 0.8; //Коэффициент понижения температуры объекта

	for (int i = 1; i < steps - 1; i++)
	{
		y[i + 1] = a * y[i] - b * y[i - 1] / 2.0 + c * u[i] + d * sin(u[i - 1]);
		u[i + 1] = u[i] * 0.8; //Коэффициент понижения температуры объекта
		std::cout << "y[" << i << "] = " << y[i] << std::endl;
	}
}
```

## Результат программы:
Вывод линейной симуляции:
Введите коэффициент a: 1
Введите коэффициент b: 1
Введите начальную температуру объекта y(0): 5
Введите начальную температуру объекта u(0): 10
y[1] = 15
y[2] = 23
y[3] = 29.4
y[4] = 34.52
y[5] = 38.616
y[6] = 41.8928
y[7] = 44.5142
y[8] = 46.6114
y[9] = 48.2891
Рассчет по нелинейной модели
Вывод нелинейной симуляции:
Введите коэффициент a: 1
Введите коэффициент b: 1
Введите коэффициент c: 1
Введите коэффициент d: 1
Введите начальную температуру объекта y(0): 10
Введите следующую температуру объекта y(1): 11
Введите начальную температуру объекта u: 50
y[1] = 11
y[2] = 45.7376
y[3] = 72.9827
y[4] = 76.2654
y[5] = 60.7044
y[6] = 39.954
y[7] = 22.0833
y[8] = 13.1069


## Reviews
suzorje
<br>
![Review for JohnyDepp228:](Comment1.png)
<br>
vimori
<br>
![Review for RisomUV:](Comment2.png)