<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Туз Г.С.</p>
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
#include<iostream>
using namespace std;

float a=0.5,
	b = 0.2,
	c= 0.15,
	d = 0.3,
	u = 1.2;
int main()
{
	float y0, y1, y2 ,y_temp;
	cout << "y1 = ?";
	cin >> y_temp;
	y1 = y_temp;
	y0 = y1;
	int n = 10;
	cout << endl << "Linear"<<endl;
	for (int i = 0; i < n; i++)
	{
		cout << "t" << i + 1 << " = ";
		y2 = a * y1 + b * u;
		cout << y2 << endl;
		y0 = y1;
		y1 = y2;
	}

	cout << endl << "Nonlinear:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "t" << i + 1 << " = ";
		y2 = a * y1 - b * y0 * y0 + c * u + d * sin(u);
		cout << y2 << endl;
		y0 = y1;
		y1 = y2;
	}

}

```

## Результат программы:
y1 = ?
1

Linear
t1 = 1.3
t2 = 0.91
t3 = 0.757
t4 = 0.6785
t5 = 0.63925
t6 = 0.619625
t7 = 0.609812
t8 = 0.604906
t9 = 0.602453
t10 = 0.601227

Nonlinear
t1 = 1.3
t2 = 0.8775
t3 = 0.697019
t4 = 0.613212
t5 = 0.573222
t6 = 0.553837
t7 = 0.544073
t8 = 0.539191
t9 = 0.536751
t10 = 0.535531
