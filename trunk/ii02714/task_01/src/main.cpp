<<<<<<< HEAD
﻿﻿#include <iostream>
=======
﻿#include <iostream>
>>>>>>> 582f740934e7c433572eaa031190b80d7753cd04
#include <cmath>
#include <vector>
using namespace std;

class Obj {
private:
	int n;
	double t;
	vector<double> y;
	vector<double> u;
	double y0;
	double temp_change;
	double a;
	double b;
	double c;
	double d;
	double c1;
	double rc;
public:
	Obj() {
		this->n = 4;
		y.resize(n, 0);
		u.resize(n, 0);
		this->t = 0;
		this->y0 = 25;
		this->a = this->b = this->c = this->d = this->c1 = this->rc = 1;
	}
	void input() {
		cout << "Cin amount of iterations: ";
		cin >> this->n;
<<<<<<< HEAD
		for (auto &n : y) {
			cout << "\nCin temperatures: ";
			cin >> n;
		}
		for (auto &n : u) {
=======
		for (auto n : y) {
			cout << "\nCin temperatures: ";
			cin >> n;
		}
		for (auto n : u) {
>>>>>>> 582f740934e7c433572eaa031190b80d7753cd04
			cout << "\nCin warm: ";
			cin >> n;
		}
		cout << "\nCin room temperature: ";
		cin >> this->y0;
		cout << "Cin const a: ";
		cin >> this->a;
		cout << "Cin const b: ";
		cin >> this->b;
		cout << "Cin const c: ";
		cin >> this->c;
		cout << "Cin const d: ";
		cin >> this->d;
		cout << "Cin const c1: ";
		cin >> this->c1;
		cout << "Cin const rc: ";
		cin >> this->rc;
	}
<<<<<<< HEAD
	void equation1(int& t) {
		this->temp_change = u.at(t) / c + (y0 - y.at(t)) / rc;
	}
	void linear(int& t) {
=======
	void eqution1(int& t) {
		this->temp_change = u.at(t) / c + (y0 - y.at(t)) / rc;
	}
	void liner(int& t) {
>>>>>>> 582f740934e7c433572eaa031190b80d7753cd04
		this->y.at(t + 1) = a * y.at(t) + b * u.at(t);
	}
	void nonlinear(int& t) {
		if (t != 0) {
			this->y.at(t + 1) = a * y.at(t) - (b * (y.at(t - 1) * y.at(t - 1))) + (c * u.at(t) + d * sin(u.at(t - 1)));
		}
		else {
			this->y.at(t + 1) = a * y.at(t) - (b * (y.at(t) * y.at(t))) + (c * u.at(t) + d * sin(u.at(t)));
		}
	}
	int getN() {
		return this->n;
	}
	int getT() {
		return this->t;
	}
	double getY(int t) {
		return this->y.at(t);
	}
	double getDelt() {
		return this->temp_change;
	}
	~Obj() {
		u.clear();
<<<<<<< HEAD

=======
>>>>>>> 582f740934e7c433572eaa031190b80d7753cd04
		y.clear();
	}
};

int main()
{
	Obj a;
	a.input();
	int n = a.getN();
	int t = a.getT();
	for (t = 0; t < n; t ++) {
		a.liner(t);
		cout << "Temperature at " << t + 1 << " equels: " << a.getY(t + 1) << endl;
	}
	return 0;
}