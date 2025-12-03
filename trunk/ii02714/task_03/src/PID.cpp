#include <vector>
#include <iostream>
#include <windows.h>
#include "PID.h"
using std::cout;
using std::cin;
using std::vector;

PID::PID() {
	deltU.resize(10000, 0);
	u.resize(10000, 0);
	y.resize(10000, 0);
	e.resize(10000, 0);
	cout << "Введите стартовое значение температуры " << endl;
	cin >> y[0];
	cout << "Введите максимальное значение температуры " << endl;
	cin >> maxTemp;
	cout << "Введите желаемое значение температуры " << endl;
	cin >> w;
	k = 0.5;
	Td = 11;
	To = 12;
	T = 11;
	a = 0.82;
	b = 0.02;
}
void PID::linear(int place) {
	PID::calcul_U(place);

	if (place == 0) {

		u[place] = 0;
	}
	else {
		y[place] = a * y[place - 1] + b * u[place - 1];

	}
}

void PID::calcul_DeltU(int place) {
	PID::calcul_e(place);
	if (place == 0) {
		deltU[place] = q0 * e[place];
	}
	else if (place == 1) {
		deltU[place] = q0 * e[place] + q1 * e[place - 1];
	}
	else {
		deltU[place] = q0 * e[place] + q1 * e[place - 1] + q2 * e[place - 2];
	}
}
void PID::calcul_U(int place) {
	PID::calcul_DeltU(place);

	if (place == 0) {
		u[place] = 0;
	}
	else {
		u[place] = u[place - 1] + deltU[place - 1];
	}
}
void PID::calcul_q0_q1_q2() {
	q0 = k * (1 + Td / To);
	q1 = -k * (1 + 2 * (Td / To) - To / T);
	q2 = k * Td / To;
}
void PID::calcul_e(int place) {
	e[place] = w - y[place];
}
void PID::calcul_PID(int place) {
	int t = place;
	double regVal = 20;
	PID::calcul_q0_q1_q2();
	for (int i = t; i < 500; i++) {
		linear(i);
		if (y[i] > w) {
			RegQs(regVal);
			RegCoefs(2);
		}
		cout << "*******************" << endl;
		cout << "Итерация: " << i << endl;
		cout << "Температура сейчас: " << y[i] << endl;
		cout << "Ошибка равна: " << e[i] << endl;
		if (y[i] >= maxTemp) {
			cout << "Достигнут максимум! " << y[i] << endl;
			break;
		}
	}
}
void PID::RegQs(double val) {
	q0 /= val;
	q1 /= val;
	q2 /= val;
	a /= val;
	b /= val;
}
void PID::RegCoefs(double val) {
	a /= val;
	b /= val;
}