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
<p align="right">Лазарчук Е.И.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (pull request) разместить его в следующем каталоге: trunk\ii0xxyy\task_01\doc (где xx - номер группы, yy - номер студента, например ii02302).
2. Исходный код написанной программы разместить в каталоге: trunk\ii0xxyy\task_01\src.
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
Task is to write program (С++), which simulates this object temperature.
## Код программы

```

#include <iostream>
#include <cmath>
using namespace std;

double Nonlinear(double a,double b,double c,double d,double y_prev,double u,double u_prev,double &y_next,double y) {
	y_next = a * y - b * (y_prev * y_prev) + c * u + d * sin(u_prev);
	return y_next;
}
double Linear(double a, double b, double y,double &y_next, double u) {
	y_next = a * y + b * u;
	return y_next;
}

int main()
{
	setlocale(LC_ALL, "RU");
	double a = 0.01;
	double b = 0.02;
	double c = 0.03;
	double d = 0.04;
	double y_next;
	double y;
	int t = 3;
	cout << "Введите начальное значение Y для линейного: " << endl;
	cin >> y;
	for (int i = 1; i < t; i++) {
		double u;
		cout << "Введите значение U на итерации: "<< i << endl;
	    cin >> u;
		double res = Linear(a, b, y, y_next, u);
		cout << "Линейное уравнение."<< endl <<"Итерация: " << i << endl<<"Результат: " << res << endl;
		y = y_next;
	}
	y = 0;
	double y_prev = 0;
	double u_prev = 0;
	y_next = 0;
	cout << endl;
	cout << "Введите начальное значение Y для нелинейного: " << endl;
	cin >> y;
	for (int i = 1; i < t; i++) {
		double u;
		cout << "Введите значение U на итерации: " << i << endl;
		cin >> u;
		double res = Nonlinear(a, b,c,d,y_prev,u,u_prev,y_next,y);
		cout << "Нелинейное уравнение." << endl << "Итерация: " << i << endl << "Результат: " << res << endl;
		y_prev = y;
		u_prev = u;
		y = y_next;
	}
	return 0;
}

```


## Результат
![Result:](res.jpg)
## Reviews
fedotovd778
<br>
![Review for :](fedotov.jpg)
<br>
GOOrst
<br>
![Review for :](Goorst.jpg)
