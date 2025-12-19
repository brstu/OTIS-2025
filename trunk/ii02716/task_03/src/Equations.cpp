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

