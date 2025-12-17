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