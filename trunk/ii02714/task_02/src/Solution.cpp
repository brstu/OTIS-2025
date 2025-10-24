#include "Solution.h"

Obj::Obj() {
	y.resize(k, 0);
	u.resize(k, 0);
	a = 1;
	b = 1;
	c = 1;
	d = 1;
	c1 = 1;
	rc = 1;
}

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
int Obj::getT() const {

	return this->t;

}
double Obj::getY(int place) const {

	return this->y.at(place);

}