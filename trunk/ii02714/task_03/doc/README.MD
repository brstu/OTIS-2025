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

#include "gtest/gtest.h"
#include "../src/Class.h"
#include "../src/PID.h"

TEST(TestClass, linearfun1) {
	Obj o;
	o.SetY(0, 1.0);
	o.SetU(0, 2.5);
	o.linear(0);
	double res = o.getY(1);
	EXPECT_NEAR(res, 3.5, 0.1);
}
TEST(TestClass, linearfun2) {
	Obj o;
	o.SetY(0, -2.0);
	o.SetU(0, 3.5);
	o.linear(0);
	double res = o.getY(1);
	EXPECT_NEAR(res, 1.5, 0.01);
}
TEST(TESTClass, funE1) {
	PID p(13,12.5);
	p.setE(3);
	double res = p.GetE(3);
	EXPECT_NEAR(res, 0.5, 0.01);
}
TEST(TESTClass, funE2) {
	PID p(2.5, 1.5);
	p.setE(3);
	double res = p.GetE(3);
	EXPECT_NEAR(res,1, 0.01);
}
TEST(TESTClass, funQ1) {
	PID p(2.5, 1.5);
	p.SetQs();
	double res = p.GetQs0();
	EXPECT_NEAR(res, 10.1,0.01);
}
TEST(TESTClass, funQ2) {
	PID p(2.5, 1.5);
	p.SetQs();
	double res = p.GetQs1();
	EXPECT_NEAR(res, -20, 0.01);
}
TEST(TESTClass, funQ3) {
	PID p(2.5, 1.5);
	p.SetQs();
	double res = p.GetQs2();
	EXPECT_NEAR(res, 10, 0.01);
}
TEST(TESTClass, funU1) {
	PID p(2.5, 1.5);
	p.SetQs();
	p.SetU(0);
	double res = p.GetUP(1);
	EXPECT_NEAR(res, 1, 0.01);
}

## Исходный код: [ otis3.cpp ]

#include <iostream>
#include <vector>
#include "../src/Class.h"
#include "../src/PID.h"


int main()
{
    PID p;
    int range = p.iterGet();
    for (int i = 0; i < range; i++) {
        p.SetU(i);
        p.SetY(i);
    }
    return 0;
}



## Исходный код: [ Class.h ]

#ifndef CLASS
#define CLASS

#include <iostream>
#include <cmath>
#include <vector>
using std::cout;
using std::cin;
using std::vector;
class Obj {
private:
	int k = 4;
	int t = 0;
	vector<double> y;
	vector<double> u;
	double y0 = 25;
	double a = 1;
	double b = 1;
	double c = 1;
	double d = 1;
	double c1 = 1;
	double rc = 1;
public:
	Obj() {
		y.resize(k, 0);
		u.resize(k, 0);
	}
	void input();
	void linear(const int& place);
	void nonlinear(const int& place);
	int getN() const;
	int getT() const;
	double getY(int place) const;
	void SetY(int place,double data);
	void SetU(int place,double data);
};


#endif

## Исходный код: [ linear.cpp ]

#include "Class.h"

using std::cout;
using std::cin;
using std::vector;

void Obj::input() {
	cout << "Enter amount of iterations: ";
	cin >> this->k;
	u.resize(k, 0);
	y.resize(k, 0);
	cout << "\nEnter temperature: ";
	cin >> y.at(0);
	for (auto& warm : u) {
		cout << "\nEnter warm: ";
		cin >> warm;
	}
	u.resize(k + 1, 0);
	y.resize(k + 1, 0);
	cout << "\nEnter room temperature: ";

	cin >> this->y0;

	cout << "Enter const a: ";

	cin >> this->a;

	cout << "Enter const b: ";

	cin >> this->b;

	cout << "Enter const c: ";

	cin >> this->c;

	cout << "Enter const d: ";

	cin >> this->d;

	cout << "Enter const c1: ";

	cin >> this->c1;

	cout << "Enter const rc: ";

	cin >> this->rc;
}
void Obj::linear(const int& place) {
	if (place <= k && place >= 0) {
		this->y.at(place + 1) = a * y.at(place) + b * u.at(place);
	}
	else {
		cout << "\nEntered place out of range";
	}
}
void Obj::nonlinear(const int& place) {

	if (place > 0 && place <= k) {
		this->y.at(place + 1) = a * y.at(place) - (b * (y.at(place - 1) * y.at(place - 1))) + (c * u.at(place) + d * sin(u.at(place - 1)));
	}
	else {
		cout << "\nEntered place out of range";
	}

}
int Obj::getN() const {

	return this->k;

}
double Obj::getY(int place) const {

	return this->y.at(place);

}
void Obj::SetU(int place, double data) {
	this->u[place] = data;
}
void Obj::SetY(int place, double data) {
	this->y[place] = data;
}

## Исходный код: [ PID.h ]

#ifndef PID_H
#define PID_H
#include <iostream>
#include <vector>
#include "../src/Class.h"


class PID : public Obj {
private:
	std::vector<double> e;
	std::vector<double> yP;
	std::vector<double> w;
	std::vector<double> u;
	std::vector<double> deltU;
	double Td;
	double To;
	double T;
	double q0;
	double q1;
	double q2;
	double k;
	int iter;
public:
	PID(double data, double data2);
	PID();
	void SetW();
	void SetY(int place);
	void SetY(int place, double data);
	void setE(int place);
	void SetQs();
	void SetU(int place);
	int iterGet();
	double GetE(int place);
	double GetYp(int place);
	double GetUP(int place);
	void SetW(int place, double data);
	double GetQs0();
	double GetQs1();
	double GetQs2();

};
#endif

## Исходный код: [ PID.cpp ]

#include <iostream>
#include <vector>
#include "../src/Class.h"
#include "../src/PID.h"

	PID::PID(double data, double data2) {
		this->iter = 10;
		e.resize(iter);
		yP.resize(iter);
		w.resize(iter);
		u.resize(iter);
		deltU.resize(iter);
		SetW(3, data);
		SetY(3, data2);
		this->T = 0.01;
		this->To = 0.01;
		this->k = 0.1;
		this->Td = 1;
		this->u[0] = 1;
		this->e[0] = 0;
		this->e[1] = 0;
		this->e[2] = 0;
	}
	PID::PID() {
		this->iter = 10;
		e.resize(iter);
		yP.resize(iter);
		w.resize(iter);
		u.resize(iter);
		deltU.resize(iter);
		this->T = 0.01;
		this->To = 0.01;
		this->k = 0.1;
		this->Td = 1;
		this->u[0] = 0;
		this->e[0] = 0;
		this->e[1] = 0;
		this->e[2] = 0;
		Obj::input();
		SetQs();
	}
	void PID::SetW() {
		for (int i = 0; i < 10; i++) {
			std::cout << "Enter w:" << std::endl;
			std::cin >> w[i];
		}
	}
	void PID::SetY(int place) {
		Obj::linear(place);
		this->yP[place] = getY(place);
	}
	void PID::SetY(int place, double data) {
		this->yP[place] = data;
	}
	void PID::setE(int place) {
		e[place] = w[place] - yP[place];
	}
	void PID::SetQs() {
		this->q0 = k * (1 + Td / To);
		this->q1 = -k * (1 + 2 * (Td / To) - To / T);
		this->q2 = k * (Td / To);
	}
	void PID::SetU(int place) {
		int placeE = 0;
		int placeQ = 0;
		if (place == 0) {
			placeQ = 1;
		}
		else {
			placeQ = place;
		}

		if (place == 0 || place == 1) {
			placeE = 2;
		}
		else if (place > 2) {
			setE(place);
		}
		deltU[place] = q0 * e[placeE] + q1 * e[placeE - 1] + q2 * e[placeE - 2];
		u[placeQ] = u[placeQ - 1] + deltU[place];
	}
	int PID::iterGet() {
		--iter;
		return iter;
	}
	double PID::GetE(int place) {
		return this->e[place];
	}
	double PID::GetYp(int place) {
		return this->yP[place];
	}
	double PID::GetUP(int place) {
		return this->u[place];
	}
	void PID::SetW(int place, double data) {
		this->w[place] = data;
	}
	double PID::GetQs0() {
		return this->q0;
	}
    double PID::GetQs1() {
		return this->q1;
	}
	double PID::GetQs2() {
		return this->q2;
	}

## Результаты юнит-тестирования (GoogleTest)

[==========] Running 8 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from TestClass
[ RUN      ] TestClass.linearfun1
[       OK ] TestClass.linearfun1 (0 ms)
[ RUN      ] TestClass.linearfun2
[       OK ] TestClass.linearfun2 (0 ms)
[----------] 2 tests from TestClass (7 ms total)

[----------] 6 tests from TESTClass
[ RUN      ] TESTClass.funE1
[       OK ] TESTClass.funE1 (0 ms)
[ RUN      ] TESTClass.funE2
[       OK ] TESTClass.funE2 (0 ms)
[ RUN      ] TESTClass.funQ1
[       OK ] TESTClass.funQ1 (0 ms)
[ RUN      ] TESTClass.funQ2
[       OK ] TESTClass.funQ2 (0 ms)
[ RUN      ] TESTClass.funQ3
[       OK ] TESTClass.funQ3 (0 ms)
[ RUN      ] TESTClass.funU1
[       OK ] TESTClass.funU1 (0 ms)
[----------] 6 tests from TESTClass (13 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 2 test suites ran. (27 ms total)
[  PASSED  ] 8 tests.