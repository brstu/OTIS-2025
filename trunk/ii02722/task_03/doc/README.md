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
<p align="right">Туз Г.С.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>
# Общее задание #
1.Написать отчет по выполненной лабораторной работе №3 в .md формате (readme.md) и разместить его в следующем каталоге: trunk\ii0xxyy\task_03\doc.
2.Исходный код написанной программы разместить в каталоге: trunk\ii0xxyy\task_03\src.
3.Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/edit/main/readme.md?#L17-L17).
4.Документировать исходный код программы с помощью комментариев в стиле Doxygen. Полученную документацию разместить в каталоге: trunk\ii0xxyy\task_03\doc\html. Настроить GitHub Pages для автоматической публикации документации из этого каталога.
5.Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием Google Test. Тесты разместить в каталоге: trunk\ii0xxyy\task_03\test



## Исходный код: [ ii02722 ]

```
#include <iostream>
#include "Model.h"

int main() {
	Const_ c(2.3, 3.4, 1.2, 1.05, 0.85, 0.05);
	Qs q(0.0, 0.0, 0.0);
	find_Qs(q, c);
	PID_model(q, c);
	return 0;
}

```

## Исходный код: [ Variables.h ]

```
#ifndef VARIABLES_H
#define VARIABLES_H

struct Qs {
	double q0;
	double q1;
	double q2;
	Qs(double q0_val, double q1_val, double q2_val) :
		q0(q0_val), q1(q1_val), q2(q2_val) {
	}
};
struct Const_ {
	double T;
	double Td;
	double To;
	double k;
	double a;
	double b;

	Const_(double T_val, double Td_val, double To_val, double k_val, double a_val, double b_val) :
		T(T_val), Td(Td_val), To(To_val), k(k_val), a(a_val), b(b_val) {
	}
};

#endif 

```
##Исходный код: [Model.h]

```
#ifndef MODEL_H
#define MODEL_H
#include "Variables.h"
/*
* \brief Class with all formulas which uses PID regulator
* 
*/
class Model {
private:
	double y;
	double u;
	double u_d;
	double y_next;
	double u_next;
	double e;
	double e_past;
	double e_past2;
	double target;
	double max;
	bool condition;
public:
/*
* \brief Constructor of class.Allowa user to initialize variables
*
*/

	Model(double y_start, double u_, double u_d_, double y_n,
		double u_n, double e_, double e_p, double e_p2, double target_, double max_, bool condition_val)
		:y(y_start), u(u_), u_d(u_d_), y_next(y_n), u_next(u_n), e(e_), e_past(e_p), e_past2(e_p2), target(target_), max(max_), condition(condition_val)
	{}
	/*
	* \brief Function for calculating Error(e)
	*
	*/

	void find_e();

/*
* \brief Function for calculating U
* \params Qs q struct with value of qs
*/

	void find_u(const Qs& q);
/*
* \brief Function which imitates linear model 
* \params Const_& c struct with value of all constants
*/
	void lin(const Const_& c);
};
/*
* \brief Function for imitation PID regulator
* \params Qs q struct with value of qs
* Const_& c struct with value of all constants
*/
void PID_model(const Qs& q, const Const_& c);
/*
* \brief Function for calculating qs
* \params Qs q struct with value of qs
* Const_& c struct with value of all constants
*/
void find_Qs(Qs& q, const Const_& c);


#endif 

```

#Исходный код: [Model.cpp]

```
#include "Model.h"
#include <iostream>

void Model::find_e() {
	e_past2 = e_past;
	e_past = e;
	e = target - y;
}
void Model::find_u(const Qs& q) {
	if (y > target) {
		condition = true;
	}
	u_d = q.q0 * e + q.q1 * e_past + q.q2 * e_past2;
	if (condition) {
		u_d = -15.0;
		condition = false;
	}
	u_next = u + u_d;
	std::cout << "U = " << u << std::endl;
	u = u_next;

}
void Model::lin(const Const_& c) {
	std::cout << "Y = " << y << std::endl;
	y_next = c.a * y + c.b * u_next;
	y = y_next;

}
void PID_model(const Qs& q, const Const_& c) {
	double s;
	double t;
	double n;
	std::cout << "Enter start temp: " << std::endl;
	std::cin >> s;
	std::cout << "Enter target temp: " << std::endl;
	std::cin >> t;
	std::cout << "Enter amout of iterations: " << std::endl;
	std::cin >> n;
	Model m(s, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, t, 300, false);
	for (int i = 0; i < n; i++) {
		std::cout << "Iteration " << i << std::endl;
		m.find_e();
		m.find_u(q);
		m.lin(c);
	}
}
void find_Qs(Qs& q, const Const_& c) {
	q.q0 = c.k * (1 + c.Td / c.To);
	q.q1 = -c.k * (1 + (2 * (c.Td / c.To)) - (c.To / c.T));
	q.q2 = c.k * (c.Td / c.To);
}

```