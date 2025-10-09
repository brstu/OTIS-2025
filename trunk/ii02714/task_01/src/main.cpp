
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Obj {
private:
	int k = 4;
	double t = 0;
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
		for (auto& temp : y) {
			cout << "\nEnter temperatures: ";
			cin >> temp;
		}
        for (auto &warm : u) {
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
	void equation1(int& t) {

		this->temp_change = u.at(t) / c + (y0 - y.at(t)) / rc;

	}
	void linear(int& t) {

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

		return this->k;

	}
	double getT() {

		return this->t;

	}
	double getY(int t) {

		return this->y.at(t);

	}
	double getDelt() {

		return this->temp_change;

	}
};
int main()
{
	Obj a;
	a.input();
	int n = a.getN();
	double t = a.getT();
	for (int j = 0; j < n; j++) {
		a.linear(j);
		cout << "Temperature at " << j + 1 << " equals: " << a.getY(j + 1) << endl;
	}
	return 0;
}
