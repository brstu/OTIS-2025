#include <iostream>
#include <cmath>
using namespace std;
struct Constant {
	double a;
	double b;
	double c;
	double d;
};
double Nonlinear(Constant &c, double y_prev, double u, double u_prev, double& y_next, double y) {
	y_next = c.a * y - c.b * (y_prev * y_prev) + c.c * u + c.d * sin(u_prev);
	return y_next;
}
double Linear(double a, double b, double y, double& y_next, double u) {
	y_next = a * y + b * u;
	return y_next;
}

int main()
{
	setlocale(LC_ALL, "RU");
	Constant k;
	k.a = 0.01;
	k.b = 0.02;
	k.c = 0.03;
	k.d = 0.04;
	double a = k.a;
	double b = k.b;
	double y_next;
	double y;
	int t = 3;
	cout << "Введите начальное значение Y для линейного: " << endl;
	cin >> y;
	for (int i = 1; i < t; i++) {
		double u;
		cout << "Введите значение U на итерации: " << i << endl;
		cin >> u;
		double res = Linear(a, b, y, y_next, u);
		cout << "Линейное уравнение." << endl << "Итерация: " << i << endl << "Результат: " << res << endl;
		y = y_next;
	}
	y = 0;
	double y_prev = 0;
	double u_prev = 0;
	y_next = 0;
	cout << endl;
	cout << "Введите начальное значение Y для нелинейного: " << endl;
	cin >> y;
	for (int i = 1; i < t; i++) {
		double u;
		cout << "Введите значение U на итерации: " << i << endl;
		cin >> u;
		double res = Nonlinear(k, y_prev, u, u_prev, y_next, y);
		cout << "Нелинейное уравнение." << endl << "Итерация: " << i << endl << "Результат: " << res << endl;
		y_prev = y;
		u_prev = u;
		y = y_next;
	}
	return 0;
}
