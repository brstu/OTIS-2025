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
<p align="right">Литвинчук И.М.</p>
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

double linear(double  y, double  u, double  a, double  b)
{
    return  a  *  y  +  b  *  u;
}
double nonlinear(double  y, double  u, double  a, double  b, double  c, double  d)
{
    return  a  *  y  -  b  *  y  *  y  +  c  *  u  +  d  *  sin(u);
}
int  main()
{
    setlocale(LC_ALL,"Russian");
	double  y, u, a, b, c, d;
	cout  <<  "Введите y, u = ";
	cin  >>  y  >>  u;
	cout  <<  "Введите а, b, c, d = ";
	cin  >>  a  >>  b  >>  c  >>  d;
	int  n;
	cout  <<  "Введите n = ";
	cin  >>  n;
	double  y1  =  y, y2  =  y;
	for (int  i  =  0; i  <  n; i++)
	{
        y1 = linear(y1, u, a, b);
		y2  =  nonlinear(y2, u, a, b, c, d);
		cout << "Шаг "  <<  i+1  <<  ", линейная y = "  <<  y1  <<  ", нелинейная y = "  <<  y2  <<  endl;
	}
	return  0;
}
```
Вывод программы:
```
Шаг 1, линейная y = 60, нелинейная y = -99.7151
Шаг 2, линейная y = 116, нелинейная y = -79620.2
Шаг 3, линейная y = 172, нелинейная y = -5.07151e+10
Шаг 4, линейная y = 228, нелинейная y = -2.05761e+22
Шаг 5, линейная y = 284, нелинейная y = -3.38702e+45
Шаг 6, линейная y = 340, нелинейная y = -9.17754e+91
Шаг 7, линейная y = 396, нелинейная y = -6.73818e+184
```