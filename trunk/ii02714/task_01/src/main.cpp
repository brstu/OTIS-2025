
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Obj {
private:
	int k = 4;
	int t = 0;
	vector<double> y;
	vector<double> u;
	double y0 = 25;
	double temp_change;
	double a = 1;
	double b = 1;
	double c = 1;
	double d = 1;
	double c1 = 1;
	double rc = 1;
public:
	Obj() {
		y.resize(k, 0);
		u.resize(k, 0);
	}
	void input() {
		cout << "Enter amount of iterations: ";
		cin >> this->k;
		u.resize(k, 0);
		y.resize(k, 0);
		for (auto& temp : y) {
			cout << "\nEnter temperatures: ";
			cin >> temp;
		}
		for (auto& warm : u) {
			cout << "\nEnter warm: ";
			cin >> warm;
		}
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
	void equation1(const int& place) {

		this->temp_change = u.at(place) / c + (y0 - y.at(place)) / rc;

	}
	void linear(const int& place) {
		if (place + 1 < k && place >= 0) {
			this->y.at(place + 1) = a * y.at(place) + b * u.at(place);
		}
		else {
			cout << "\nEntered place out of range";
		}

	}
	void nonlinear(const int& place) {

		if (place > 0 && place + 1 <= k) {
			this->y.at(place + 1) = a * y.at(place) - (b * (y.at(place - 1) * y.at(place - 1))) + (c * u.at(place) + d * sin(u.at(place - 1)));
		}
		else {
			cout << "\nEntered place out of range";
		}

	}
	 int getN() const {

		return this->k;

	}
	 int getT() const {

		return this->t;

	}
	 double getY(int place) const {

		return this->y.at(place);

	}
	double getDelt() const {

		return this->temp_change;

	}
};
int main()
{
	Obj a;
	a.input();
	int n = a.getN();
	int t = a.getT();
	for (int j = t; j < n -1; j++) {
		a.linear(j);
		cout << "Linear equation: Temperature at " << j + 1 << " equals: " << a.getY(j + 1) << endl;
		a.equation1(j);
		cout << "Temperature change at " << j << " is: " << a.getDelt() << endl;
	}
	for (int m = t; m < n -1; m++) {
		a.nonlinear(m);
		cout << "Nonlinear equation: Temperature at " << m + 1 << " equals: " << a.getY(m + 1) << endl;
		a.equation1(m);
		cout << "Temperature change at " << m << " is: " << a.getDelt() << endl;
	}
	return 0;
}
