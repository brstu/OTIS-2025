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
<p align="right">Масюк А.Д.</p>
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
#include "../src/PID.h"

TEST(TestClass, chekQs2) {
	Qs q;
	q.T = 2.5;
	q.To = 1.3;
	q.Td = 1.4;
	q.k = 1.5;
	findQ(q);
	double res1 = q.q0;
	double res2 = q.q0;
	double res3 = q.q0;
	EXPECT_NEAR(res1, 3, 0.1);
	EXPECT_NEAR(res2, 3, 0.1);
	EXPECT_NEAR(res3, 3, 0.1);
}
```

## Исходный код: [ main.cpp ]

```
#include <iostream>
#include "PID.h"

int main()
{
   Arg g;
   Qs q;
   PID(q, g);
   return 0;
}
```

## Исходный код: [ PID.h ]

```
#ifndef PID_H
#define PID_H
#include <vector>

struct Arg {
	std::vector<double> y;
	std::vector<double> u;
	std::vector<double> e;
	std::vector<double> delt_u;
	double a;
	double b;
	double w;
	double maxT;
};
struct Qs
{
	double k;
	double To;
	double Td;
	double T;
	double q0;
	double q1;
	double q2;
};

void linearMod(Arg& g, const int& place);
void E(Arg& g, const int& place);
void findQ(Qs& q);
void findU(Qs& q,Arg& g, const int& place);
void ReqQ(Qs& q);
void PID(Qs& q, Arg& g);

#endif 
```

## Исходный код: [ PID.cpp ]

```
#include "PID.h"
#include <iostream>

using namespace std;

void linearMod(Arg& g, const int& place) {
	g.y[place + 1] = g.a * g.y[place] + g.b * g.u[place];
}
void E(Arg& g, const int& place) {
	g.e[place] = g.w - g.y[place];
}
void findU(Qs& q,Arg& g, const int& place) {
	if (place >= 2) {
       g.delt_u[place] = q.q0 * g.e[place] + q.q1 * g.e[place  - 1] + q.q2 * g.e[place - 2];
	}
	g.u[place + 1] = g.u[place] + g.delt_u[place];
	
}
void findQ(Qs& q) {
	q.k = 1.5;
	q.To = 1.3;
	q.Td = 1.3;
	q.T = 1.5;
	q.q0 = q.k * (1 + q.Td / q.To);
	q.q1 = -q.k * (1 + 2 * (q.Td / q.To) - q.To / q.T);
	q.q2 = q.k * q.Td / q.To;
}
void ReqQ(Qs& q) {
	q.k -= 0.05;
	q.To -= 0.05;
	q.Td -= 0.05;
	q.T -= 0.05;
}
void PID(Qs& q, Arg& g) {
	g.y.resize(500, 0);
	g.u.resize(500, 0);
	g.e.resize(500, 0);
	g.delt_u.resize(500, 0);
	g.delt_u[0] = 0;
	g.delt_u[1] = 0;
	g.u[0] = 0;
	g.e[0] = 0;
	g.e[1] = 0;
	cout << "Enter max temperauteru: " << endl;
	cin >> g.maxT;
	cout << "Enter desired temperauteru: " << endl;
	cin >> g.w;
	cout << "Enter start temperauteru: " << endl;
	cin >> g.y[0];
	g.a = 0.85;
	g.b = 0.05;
	findQ(q);
	for (int i = 0; i < 200; i++) {
		cout << "Iteration numder " << i + 1 << endl;
		E(g, i);
		cout << "Error: " << g.e[i] << endl;
		findU(q, g, i);
		linearMod(g, i);
		cout << "Temperature: " << g.y[i] << endl;
		if (g.y[i] > g.w) {
			ReqQ(q);
			findQ(q);
		}
		if (g.y[i] > g.maxT) {
			cout << "Max temperature" << endl;
			break;
		}
		cout << "*****************" << endl;
	}
}
```

## Результаты юнит-тестирования (GoogleTest)

[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from TestClass
[ RUN      ] TestClass.chekQs2
[       OK ] TestClass.chekQs2 (0 ms)
[----------] 1 test from TestClass (1 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (5 ms total)
[  PASSED  ] 1 test.