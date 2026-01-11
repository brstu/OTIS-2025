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
<p align="right">Ничипорчик Д.А.</p>
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
#include "../src/Equations.h"

TEST(TestFuns, LinearModel_chek1) {
	Equations eq(1.2, 1.4, 1.5, 1.6);
	Constunts con = { 0.85,0.05,1.5,1.2,1.4,1.6 };
	eq.LinearModel(con);
	double res;
	res = eq.GetY();
	EXPECT_NEAR(res, 1.25, 0.1);
}
TEST(TestFuns, LinearModel_chek2) {
	Equations eq(0.2, 0.4, 0.5, 0.6);
	Constunts con = { 0.85,0.05,1.5,1.2,1.4,1.6 };
	eq.LinearModel(con);
	double res;
	res = eq.GetY();
	EXPECT_NEAR(res,0.35, 0.1);
}
```

## Исходный код: [ otis3s.cpp ]

```
#include <iostream>
#include "PID.h"

int main()
{

	PID(50.0);
    return 0;
}

```

## Исходный код: [ PID.h ]

```
#ifndef PID_H
#define PID_H
#include "Equations.h"
#include <iostream>
/**
* \brief Function which imitates PID regulator
*/
void PID(double val);
#endif 
```

## Исходный код: [ PID.cpp ]

```
#include "PID.h"
using namespace std;

void PID(double val) {
	Constunts con = { 0.85,0.05,1.5,1.2,1.4,1.6 };
	double err;
	double u;
	double y;
	Equations e(2.3, 4.5, 0.0, 5.7);
	e.Qs_calcul(con);
	e.SetW(val);
	for (int i = 0; i < 200; i++) {
		e.E_calcul(i);
		err = e.Get_E(i);
		std::cout << "Error on iteration " << i << " = " << err << std::endl;
		e.U_calcul(i);
		u = e.GetU();
		std::cout << "U on iteration " << i << " = " << u << std::endl;
		e.LinearModel(con);
		y = e.GetY();
		std::cout << "Y on iteration " << i << " = " << y << std::endl;
		if (!e.chek()) {
			e.SetDelt_U(10);
		}
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
	}
}
```
## Исходный код: [ Equations.cpp ]

```
#include "Equations.h"

void Equations::LinearModel(const Constunts& k) {
	y = k.a * y_prev + k.b * u;
	y_prev = y;
}
void Equations::U_calcul(int place) {
	if (place >= 2) {
		delt_u = q0 * e[place] + q1 * e[place - 1] + q2 * e[place - 2];
	}
	else {
		delt_u = 0;
	}
	f_u = u + delt_u;
	u = f_u;
}
void Equations::Qs_calcul(const Constunts& c) {
	q0 = c.k * (1 + c.Td / c.To);
	q1 = -c.k * (1 + 2 * (c.Td / c.To) - (c.To / c.T));
	q2 = c.k * (c.Td / c.To);
}
void Equations::E_calcul(int place) {
	e[place] = w - y;
}
double Equations::GetY() {
	return y;
}
double Equations::GetU() {
	return u;
}
void Equations::SetDelt_U(double val) {
	delt_u = val;
}
double Equations::Get_E(int place) {
	return e[place];
}
bool Equations::chek() {
	return w > y_prev;
}
void Equations::SetW(double w) {
	this->w = w;
}

```
## Исходный код: [ Equations.h ]

```
#ifndef EQUATION_H
#define EQUATION_H
#include <vector>

/**
* \brief Struct with constants
*/
struct Constunts
{
	double a;
	double b;
	double T;
	double To;
	double Td;
	double k;

};
/**
* \brief CLass consist of equations used in PID regulator
*/
class Equations {
private:
	std::vector<double> e;
	double q0;
	double q1;
	double q2;
	double u;
	double f_u;
	double y_prev;
	double y;
	double delt_u;
	double w;
public:
/**
* \brief Constructor for init variables used in equations
*/
	Equations(double u_val, double y_prev_val, double delt_u_val,double w_val) :
		u(u_val), y_prev(y_prev_val), delt_u(delt_u_val), w(w_val), f_u(1.5), q0(0), q1(0), q2(0), y(0) {
		e.resize(500, 0);
	}
	/**
	* \brief Imitation of linear model
	* \param const Constunts& k is struct with all constants
	*/
	void LinearModel(const Constunts& k);
	/**
	* \brief Calculating of U and delta_U
	* \param place uses for controlling outrange of vector
	*/
	void U_calcul(int place);
	/**
	* \brief Calculates q0 q1 q2
	* \param const Constunts& k is struct with all constants
	*/
	void Qs_calcul(const Constunts& c);
	/**
	* \brief Calculates error e
	* \param place uses for controlling outrange of vector
	*/
	void E_calcul(int place);
	double GetY();
	double GetU();
	void SetDelt_U(double val);
	double Get_E(int place);
	/**
	* \brief Checking if temperature already have reached necessary temp
	* return true if reached and false if not
	*/
	bool chek();
	void SetW(double w);
};

#endif 
```
## Результаты юнит-тестирования (GoogleTest)
