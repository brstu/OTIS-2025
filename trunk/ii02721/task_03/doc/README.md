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
<p align="right">Федотов Д.А.</p>
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

## Исходный код: [ main.cpp]

```
#include "PID.h"

int main(){
double temp;
double desired_temp;
std::cout << "Enter desired temp " << std::endl;
std::cin >> desired_temp;
std::cout << "Enter start temp " << std::endl;
std::cin >> temp;
PID_model(desired_temp,temp);
return 0;
}

```

## Исходный код: [ PID.h ]

```
#ifndef PID_H
#define PID_H

#include "Model.h"
#include <iostream>

void PID_model(double desired_temp,double start);

#endif 
};
#endif 

```

## Исходный код: [ PID.cpp ]

```
#include "PID.h"

void PID_model(double desired_temp,double start){
Models m(start,0.0,0.0,desired_temp);
Constants con(0.85,0.05,1.2,1.3,1.3,1.3);
Qs q(0.0,0.0,0.0);
m.calcul_Q(q,con);
for(int i = 0;i < 200;i++){
m.calcul_err(i);
double err = m.GetE(i);
std::cout << "Error = " << err << std::endl;
m.calcul_u(q,i);
double u = m.GetU();
std::cout << "U = " << u << std::endl;
m.linear(con);
double y = m.GetY();
std::cout << "Y = " << y << std::endl;
if(!m.compare()){
m.SetDelt(15.0);
	} 
			}

}

```
##Исходный код: [Model.h]

```
#ifndef MODEL_H
#define MODEL_H
#include <vector>
/**
*\brief Struct for constants

*/
struct Constants
{
	double a;
	double b;
	double k;
	double To;
	double T;
	double Td;

	Constants(double a_, double b_, double k_, double To_, double T_, double Td_)
        : a(a_), b(b_), k(k_), To(To_), T(T_), Td(Td_) {}
};
/**
*\brief Struct for resalt of Qs
*/
struct Qs{
	double q0;
	double q1;
	double q2;

	 Qs(double q0_, double q1_, double q2_) : q0(q0_), q1(q1_), q2(q2_) {}
};
/**
*\brief  Class consist of method for PID
*/
class Models{
private:
	double y_prev;
	double y;
	double u;
	double u_prev;
	std::vector<double> e;
	double delt_u;
	double desired_temp;
	double w;
public:
/**
*\brief Constructor for init variables
*/
	Models(double y_prev_val,double u_prev_val,double delt_u_val,double w_val)
	:y_prev(y_prev_val),u_prev(u_prev_val),delt_u(delt_u_val),w(w_val){}
/**
*\brief Calculating error
*/
	void calcul_err(int place);
/**
*\brief Calculating Q
*/
	void calcul_Q(Qs &q,const Constants &con);
/**
*\ brief Calculating Qs
*/
	void calcul_u(const Qs &q,int place);
/**
*\brief Imitation of linear model
*/
	void linear(const Constants &con);
/**
*\brief Uses for comoaring w and y
*return true or false
*/
	bool compare() const;
	void SetDelt(double val);
	double GetE(int place) const;
	double GetY() const;
	double GetU() const;
};


#endif
```
#Исходный код: [Model.cpp]

```
#include "Model.h"

void Models::calcul_err(int place){
e.resize(500,0);
e[place] = w - y_prev;
}
void Models::calcul_Q(Qs &q,const Constants &con){
q.q0 = con.k * (1 + con.Td/con.To);
q.q1 = -con.k * (1 + 2 * con.Td/con.To - con.To/con.T);
q.q2 = con.k * con.Td/con.To;
}
void Models::calcul_u(const Qs &q,int place){
if(place > 2){
 delt_u = q.q0 * e[place] + q.q1 * e[place - 1] + q.q2 * e[place - 2];
}
else{
delt_u = q.q0 * e[place];
}
u = u_prev + delt_u;
u_prev = u;
}
void Models::linear(const Constants &con){
y = con.a * y_prev + con.b * u;
y_prev = y;
}

bool Models::compare() const{
return w > y_prev;
}

void Models::SetDelt(double val){
delt_u = val;
}
double Models::GetE(int place) const{
return e[place];
}
double Models::GetY() const{
return y;
}
double Models::GetU() const{
return u;
}

```
