#include "PID.h"
#include <iostream>
using namespace std;

PID::PID() {
	y.resize(500, 0);
	e.resize(500, 0);
	u.resize(500, 0);
	d_u.resize(500, 0);
	cout << "Enter start temp" << endl;
	cin >> y[0];
	cout << "Enter max temp" << endl;
	cin >> max;
	cout << "Enter necessary temp" << endl;
	cin >> w;
	PID::init();
}
void PID::init() {
	a = 0.85;
	b = 0.05;
	k = 1.5;
	To = 1.3;
	Td = 1.3;
	T = 1.5;
	q0 = 0;
	q1 = 0;
	q2 = 0;
	u[0] = 0;
	d_u[0] = 0;
	d_u[1] = 0;
	e[0] = 0;
	e[1] = 0;
}
void PID::E(int place) {
	e[place] = w - y[place];
}
void PID::Qs() {
	q0 = k * (1 + Td / To);
	q1 = -k * (1 + 2 * (Td / To) - To / T);
	q2 = k * Td / To;
}
void PID::GetQ(double &val, double& val1, double& val2) const  {
	val = q0;
	val1 = q1;
	val2 = q2;
}
void PID::U(int place) {
	if (place >= 2) {
		d_u[place] = q0 * e[place] + q1 * e[place - 1] + q2 * e[place - 2];
	}
	u[place + 1] = u[place] + d_u[place];
}
void PID::lin(int place) {
	y[place + 1] = a * y[place] + b * u[place];
}
void PID::Model() {
	PID::Qs();
	for (int i = 0; i < 200; i++) {
		cout << "Iteration " << i + 1 << endl;
		PID::E(i);
		cout << "Error: " << e[i] << endl;
		PID::U(i);
		PID::lin(i);
		cout << "Temperature: " << y[i] << endl;
		if (y[i] > w) {
			d_u[i] = 10.0;
		}
		if (y[i] > max) {
			cout << "Max temperature" << endl;
			break;
		}
		cout << "########################" << endl;
	}
}
