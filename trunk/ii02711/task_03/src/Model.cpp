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
		if (y[i] > w) {
			d_u[i] = 15.0;
		}
		if (y[i] > max) {
			cout << "Max temperature" << endl;
			break;
		}
		cout << endl << endl;
	}
}