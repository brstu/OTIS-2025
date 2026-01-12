<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы”</p>
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
1.Написать отчет по выполненной лабораторной работе №3 в .md формате (readme.md) и разместить его в следующем каталоге: trunk\ii0xxyy\task_03\doc.
2.Исходный код написанной программы разместить в каталоге: trunk\ii0xxyy\task_03\src.
3.Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/edit/main/readme.md?#L17-L17).
4.Документировать исходный код программы с помощью комментариев в стиле Doxygen. Полученную документацию разместить в каталоге: trunk\ii0xxyy\task_03\doc\html. Настроить GitHub Pages для автоматической публикации документации из этого каталога.
5.Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием Google Test. Тесты разместить в каталоге: trunk\ii0xxyy\task_03\test.

## Код юнит-тестов [ test/test.cpp ]

```
#include "gtest/gtest.h"
#include "../src/Model.h"

TEST(TestClass, chekQs2) {
	PID_reg p;
	p.Qs_find();
	double res1;
	double res2;
	double res3;
	p.GetQ(res1, res2, res3);
	EXPECT_NEAR(res1, 3, 0.1);
	EXPECT_NEAR(res2, -3.2, 0.1);
	EXPECT_NEAR(res3, 1.5, 0.1);
}
```

## Исходный код: [ main.cpp ]

```
#include <iostream>
#include "Model.h"

int main()
{
	PID_reg p;
	p.Imitation();
    return 0;
}
```

## Исходный код: [ Model.h ]

```
#ifndef PID_H
#define PID_H
#include <vector>

class PID_reg {
private:
	std::vector<double> e;
	std::vector<double> y;
	std::vector<double> u;
	std::vector<double> d_u;
	double T;
	double To;
	double Td;
	double k;
	double q0;
	double q1;
	double q2;
	double w;
	double max;
	double a;
	double b;
public:
	PID_reg();
	void Qs_find();
	void E_find(int place);
	void U_find(int place);
	void lin(int place);
	void Imitation();
	void GetQ(double& val, double& val1, double& val2) const;
	void init();
};
#endif 
```

## Исходный код: [ Model.cpp ]

```
#include "Model.h"
#include <iostream>
using namespace std;

PID_reg::PID_reg() {
	y.resize(500, 0);
	e.resize(500, 0);
	u.resize(500, 0);
	d_u.resize(500, 0);
	cout << "Start temp: " << endl;
	cin >> y[0];
	cout << "Max temp: " << endl;
	cin >> max;
	cout << "Temp to achive" << endl;
	cin >> w;
	PID_reg::init();
}
void PID_reg::init() {
	a = 0.85;
	b = 0.05;
	k = 1.5;
	To = 1.3;
	Td = 1.3;
	T = 1.5;
	u[0] = 0;
	d_u[0] = 0;
	d_u[1] = 0;
	e[0] = 0;
	e[1] = 0;
}
void PID_reg::E_find(int place) {
	e[place] = w - y[place];
}
void PID_reg::Qs_find() {
	q0 = k * (1 + Td / To);
	q1 = -k * (1 + 2 * (Td / To) - To / T);
	q2 = k * Td / To;
}
void PID_reg::GetQ(double &val, double& val1, double& val2) const  {
	val = q0;
	val1 = q1;
	val2 = q2;
}
void PID_reg::U_find(int place) {
	if (place >= 2) {
		d_u[place] = q0 * e[place] + q1 * e[place - 1] + q2 * e[place - 2];
	}
	u[place + 1] = u[place] + d_u[place];
}
void PID_reg::lin(int place) {
	y[place + 1] = a * y[place] + b * u[place];
}
void PID_reg::Imitation() {
	PID_reg::Qs_find();
	for (int i = 0; i < 200; i++) {
		cout << "Iteration " << i + 1 << endl;
		PID_reg::E_find(i);
		cout << "Error =  " << e[i] << endl;
		PID_reg::U_find(i);
		PID_reg::lin(i);
		cout << "Temperature = " << y[i] << endl;
		if (y[i] > max) {
			cout << "Max temperature" << endl;
			break;
		}
		if (y[i] > w) {
			d_u[i] = 15.0;
		}
		cout << endl << endl;
	}
}
```

## Результаты юнит-тестирования (GoogleTest)
