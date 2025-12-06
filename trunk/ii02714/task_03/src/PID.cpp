#include <vector>
#include <iostream>
#include "PID.h"
using std::cout;
using std::cin;
using std::vector;

PID::PID() {
	deltU.resize(10000, 0);
	u.resize(10000, 0);
	y.resize(10000, 0);
	e.resize(10000, 0);
	cout << "Введите стартовое значение температуры " << std::endl;
	cin >> y[0];
	cout << "Введите максимальное значение температуры " << std::endl;
	cin >> maxTemp;
	cout << "Введите желаемое значение температуры " << std::endl;
	cin >> w;
}
void PID::linear(int place) {
	a = 0.82;
	b = 0.2;
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
	k = 0.5;
	Td = 11;
	To = 12;
	T = 11;
	q0 = k * (1 + Td / To);
	q1 = -k * (1 + 2 * (Td / To) - To / T);
	q2 = k * Td / To;
}
void PID::calcul_e(int place) {
	e[place] = w - y[place];
}
void PID::calcul_PID(int place) {
	int t = place;
	PID::calcul_q0_q1_q2();
	for (int i = t; i < 100; i++) {
		linear(i);
		if (y[i] > w) {
			
			RegCoefs(10);
		}
		cout << "*******************" << std::endl;
		cout << "Итерация: " << i+1 << std::endl;
		cout << "Температура сейчас: " << y[i] << std::endl;
		cout << "Ошибка равна: " << e[i] << std::endl;
		if (y[i] >= maxTemp) {
			cout << "Достигнут максимум! " << y[i] << std::endl;
			break;
		}
	}
}
void PID::RegCoefs(double val) {
	a /= val;
	b /= 1.3;
}
void PID::GetQs(double& val1, double& val2, double& val3) const {
	val1 = q0;
	val2 = q1;
	val3 = q2;
}