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
<p align="right">Асташёнок Д.С.</p>
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
	double  y, u, a, b, c, d;
	cout  <<  "y, u = ";
	cin  >>  y  >>  u;
	cout  <<  "а, b, c, d = ";
	cin  >>  a  >>  b  >>  c  >>  d;

	int  n;
	cout  <<  "n = ";
	cin  >>  n;

	double  y1  =  y, y2  =  y;
	for (int  i  =  0; i  <  n; i++)
	{
        y1 = linear(y1, u, a, b);
		y2  =  nonlinear(y2, u, a, b, c, d);
		cout << "Step "  <<  i+1  <<  ", linear y = "  <<  y1  <<  ", n-linear y = "  <<  y2  <<  endl;
	}

	return  0;
}
```
Вывод программы:
```
y, u = 1 2
а, b, c, d = 0.9 0.8 0.67 0.42
n = 10
Step 1, linear y = 2.5, n-linear y = 1.8219
Step 2, linear y = 3.85, n-linear y = 0.706149
Step 3, linear y = 5.065, n-linear y = 1.95852
Step 4, linear y = 6.1585, n-linear y = 0.415928
Step 5, linear y = 7.14265, n-linear y = 1.95784
Step 6, linear y = 8.02839, n-linear y = 0.417444
Step 7, linear y = 8.82555, n-linear y = 1.9582
Step 8, linear y = 9.54299, n-linear y = 0.416654
Step 9, linear y = 10.1887, n-linear y = 1.95801
Step 10, linear y = 10.7698, n-linear y = 0.417064
```