#include <iostream>
#include <cmath>
using namespace std;

class Obj {
private:
	int n;
	double t;
	double *y;
	double *u;
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
		this->y = new double[n];
		for (int i = 0; i < n; i++) {
			 *(y + i) = 0;
		}
		this-> u = new double[n];
		for (int i = 0; i < n; i++) {
			*(u + i) = 0;
		}
	    this->t = 0;
		this->y0 = 25;
		this->a = this->b = this->c = this->d = this->c1 = this->rc = 1;
	}
	void input() {
		delete[] y;
		delete[] u;
		cout << "Cin amount of iterations: ";
		cin >> this->n;
		this->y = new double[n];
		for (int i = 0; i < n;i++) {
				cout << "\nCin temperatures: ";
				cin >> *(y+i);
			}
		this->u = new double[n];
		for (int i = 0; i < n; i++) {
			cout << "\nCin warm: ";
			cin >> *(u + i);
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
	void eqution1(int &t) {
		this->temp_change = u[t] / c + (y0 - y[t]) / rc;
	}
	void liner(int& t) {
		this-> y[t + 1] = a * y[t] + b * u[t];
	}
	void neliner(int& t) {
		if (t != 0) {
			this->y[t + 1] = a * y[t] - (b * (y[t - 1] * y[t - 1])) + (c * u[t] + d * sin(u[t - 1]));
		}
		else {
			this->y[t + 1] = a * y[t] - (b * (y[t] * y[t])) + (c * u[t] + d * sin(u[t]));
		}
	}
	int getN() {
		return this->n;
	}
	int getT() {
		return this->t;
	}
	double getY(int t) {
		return this->y[t];
	}
	double getDelt() {
		return this->temp_change;
	}
	~Obj() {
		delete[] y;
		delete[] u;
	}
};

int main()
{
	Obj a;
	a.input();
	int n = a.getN();
	int t = a.getT();
	for (t = 0; t < n; t += a.getDelt()) {
		a.liner(t);
		cout << "Temperature at " << t + 1 << "equels: " << a.getY(t + 1) << endl;
	}
	return 0;
}
