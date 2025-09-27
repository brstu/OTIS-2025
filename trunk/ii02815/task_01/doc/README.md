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
using namespace std;

double linearModel(double y, double u, double a, double b) {
	return a * y + b * u;
}

double nonlinearModel(double y, double y_prev, double u, double u_prev, double a, double b, double c, double d) {
	return a * y - b * y_prev * y_prev + c * u + d * sin(u_prev);
}

int main() {
	setlocale(LC_ALL,"RU");
	double a, b, c, d;
	double y0, u0;
	int n;

	cout << "Введите константы a, b, c, d: ";
	cin >> a >> b >> c >> d;

	cout << "Введите начальное значение температуры y(0): ";
	cin >> y0;

	cout << "Введите начальное значение теплоты u(0): ";
	cin >> u0;

	cout << "Введите число шагов: ";
	cin >> n;

	double y_linear = y0;
	double y_nonlinear = y0;
	double u = u0;

	cout << "Шаги\tЛинейная модель\tНелинейная модель\n";

	for (int step = 1; step <= n; ++step) {
		double linear_result = linearModel(y_linear, u, a, b);
		double nonlinear_result = nonlinearModel(y_nonlinear, y_nonlinear, u, u, a, b, c, d);

		cout << step << "\t" << linear_result << "\t\t" << nonlinear_result << "\n";

		y_linear = linear_result;
		y_nonlinear = nonlinear_result;
	}

	return 0;
}

```
Вывод программы:
```
Введите константы a, b, c, d: 1.2 0.8 0.96 1.6
Введите начальное значение температуры y(0): 1
Введите начальное значение теплоты u(0): 1
Введите число шагов: 10
Шаги    Линейная модель Нелинейная модель
1       2               2.70635
2       3.2             -0.305502
3       4.64            1.86509
4       6.368           1.76162
5       8.4416          1.93765
6       10.9299         1.62794
7       13.9159         2.13974
8       17.4991         1.21126
9       21.7989         2.58614
10      26.9587         0.0592117
```