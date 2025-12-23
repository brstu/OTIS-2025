<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа N1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Гурин М.Д.</p>
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
#include <iostream>
#include <cmath>
using namespace std;

void liner_funcnt(double& y1)
{
	double first_funct_const = 0.1;
	double second_funct_const = 0.2;
	double third_funct_const = 0.3;
	y1 = first_funct_const * y1 + second_funct_const * third_funct_const;
	cout << y1 << endl;
}

void quadro_funct(double& y2, double& y_previous, bool& first_iteration)
{
	double first_funct_const = 0.1;
	double second_funct_const = 0.2;
	double third_funct_const = 0.3;
	double fourth_funct_const = 0.4;
	double fifth_funct_const = 0.5;
	if (first_iteration)
	{
		y_previous = y2;
		y2 = first_funct_const * y2 + fourth_funct_const * third_funct_const + fourth_funct_const * sin(third_funct_const); 
		cout << y2 << endl;
		first_iteration = false;
	}
	else
	{
		double buf;
		buf = first_funct_const * y2 - second_funct_const * pow(y_previous, 2) + fourth_funct_const * third_funct_const + fifth_funct_const * sin(third_funct_const);
		y_previous = y2;
		y2 = buf;
		cout << y2 << endl;
	}
}


int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double y1, y2, y_previous;
	bool first_iteration = true;
	cout << "Введите вашу термепаруту: ";
	cin >> y1;
	y2 = y1;
	int n = 20;
	cout << "Линейная модель:\n" << y1 << endl;
	for (int i = 0; i < n; i++)
	{
    liner_funcnt(y1);
	}
	cout << endl << "Квадратичная модель:\n" << y2 << endl;
	for (int i = 0; i < n; i++)
	{
		quadro_funct(y2, y_previous, first_iteration);
	}
}
``` 
```
Линейная модель
3
0.36
0.096
0.0696
0.06696
0.066696
0.0666696
0.066667
0.0666667
0.0666667
0.0666667
0.0666667
0.0666667
0.0666667
0.0666667

Квадратичная модель
3
0.538208
-1.47842
0.0619846
-0.163186
0.250673
0.287501
0.283943
0.279623
0.279598
0.280082
0.280133
0.280084
0.280074
0.280078
0.28008
0.280079
```