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
<p align="right">Степанюк А.С.</p>
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

int  main()

{
	double  y, u, a, b, c, d;
	cout  <<  "Enter y and u values:\n";
	cin  >>  y  >>  u;
	cout  <<  "Enter a, b, c, d values:\n";
	cin  >>  a  >>  b  >>  c  >>  d;

	int  n;
	cout  <<  "Enter number of steps n: ";
	cin  >>  n;

	double  y1  =  y, y2  =  y;
	for (int  i  =  0; i  <  n; i++)
	{
		y1  =  a  *  y1  +  b  *  u;
		y2  =  a  *  y2  -  b  *  y2  *  y2  +  c  *  u  +  d  *  sin(u);
		cout  <<  "Result of the "  <<  i  +  1  <<  "st step of linear model: "  <<  y1  <<  ";\n";
		cout  <<  "Result of the "  <<  i  +  1  <<  "st step of non-linear model: "  <<  y2  <<  ";\n";
	}

	return  0;
}
```
Вывод программы:
```
Enter y and u values:
1 1
Enter a, b, c, d values:
1.1 0.9 0.85 1.4
Enter number of steps n: 10
Result of the 1st step of linear model: 2;
Result of the 1st step of non-linear model: 2.22806;
Result of the 2st step of linear model: 3.1;
Result of the 2st step of non-linear model: 0.011101;
Result of the 3st step of linear model: 4.31;
Result of the 3st step of non-linear model: 2.04016;
Result of the 4st step of linear model: 5.641;
Result of the 4st step of non-linear model: 0.526209;
Result of the 5st step of linear model: 7.1051;
Result of the 5st step of non-linear model: 2.35768;
Result of the 6st step of linear model: 8.71561;
Result of the 6st step of non-linear model: -0.381291;
Result of the 7st step of linear model: 10.4872;
Result of the 7st step of non-linear model: 1.47779;
Result of the 8st step of linear model: 12.4359;
Result of the 8st step of non-linear model: 1.68815;
Result of the 9st step of linear model: 14.5795;
Result of the 9st step of non-linear model: 1.32017;
Result of the 10st step of linear model: 16.9374;
Result of the 10st step of non-linear model: 1.91168;
```
## Рецензирование запросов других студентов ##
![Рецензия работы пользователя threenebula23:](https://i.ibb.co/mF8Trkgx/img1.png)

![Комментарий к коду пользователя oniisssss:](https://i.ibb.co/pvTVwcQ6/img2.png)
