#include <iostream>
#include <cmath>
using namespace std;

double Nonlinear(double a, double b, double c, double d, double y_prev, double u, double u_prev, double& y_next, double y) {
	y_next = a * y - b * (y_prev * y_prev) + c * u + d * sin(u_prev);
	return y_next;
}
double Linear(double a, double b, double y, double& y_next, double u) {
	y_next = a * y + b * u;
	return y_next;
}

int main()
{
	setlocale(LC_ALL, "RU");
	double a = 0.01;
	double b = 0.02;
	double c = 0.03;
	double d = 0.04;
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
		double res = Nonlinear(a, b, c, d, y_prev, u, u_prev, y_next, y);
		cout << "Нелинейное уравнение." << endl << "Итерация: " << i << endl << "Результат: " << res << endl;
		y_prev = y;
		u_prev = u;
		y = y_next;
	}
	return 0;
}
