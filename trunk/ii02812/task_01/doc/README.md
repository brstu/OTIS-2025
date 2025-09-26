
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
using  namespace  std;

double lin(double  y, double  u, double  a, double  b)
{

	return a * y + b * u;
}

double nonlin(double& y0, double& y1, double u, double a, double b, double c, double d)
{
	y0 = y1;
	y1 = a * y1 - b * pow(y0, 2) + c * u + d * sin(u);
	return y1;
}

int  main()
{
	setlocale(LC_ALL, "RUS");
	double  y = 0,
		u = 0,
		a = 0,
		b = 0,
		c = 0,
		d = 0;

	int  n = 0;

	cout << "Введите значение температуры (y): ";
	cin >> y;
	cout << "Введите значение теплоты (u): ";
	cin >> u;
	double y0 = 0,
		y1 = y,
		y2 = 0;
	cout << "Введите константы а, b, c, d: ";
	cin >> a >> b >> c >> d;

	cout << "Введите кол-во шагов: ";
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		y = lin(y, u, a, b);
		y2 = nonlin(y0,y1,u,a, b, c, d);
		cout << "Шаг " << i
			<< ", Температура линейной функц. = "<< y
			<< ",Температура нелинейной функц. = " << y2 << endl;
	}

	return  0;
}
```

Вывод программы:

```

Введите значение температуры (y): 2
Введите значение теплоты (u): 20
Введите константы а, b, c, d: 0.2
0.02
0.4
0.1
Введите кол-во шагов: 9
Шаг 1, Температура линейной функц. = 0.8,Температура нелинейной функц. = 8.41129
Шаг 2, Температура линейной функц. = 0.56,Температура нелинейной функц. = 8.35856
Шаг 3, Температура линейной функц. = 0.512,Температура нелинейной функц. = 8.3657
Шаг 4, Температура линейной функц. = 0.5024,Температура нелинейной функц. = 8.36474
Шаг 5, Температура линейной функц. = 0.50048,Температура нелинейной функц. = 8.36487
Шаг 6, Температура линейной функц. = 0.500096,Температура нелинейной функц. = 8.36485
Шаг 7, Температура линейной функц. = 0.500019,Температура нелинейной функц. = 8.36485
Шаг 8, Температура линейной функц. = 0.500004,Температура нелинейной функц. = 8.36485
Шаг 9, Температура линейной функц. = 0.500001,Температура нелинейной функц. = 8.36485

```
