#include <iostream>
#include <cmath>
using namespace std;

double linearModel(double y, double u, double a, double b) {
	return a * y + b * u;
}

double nonlinearModel(double y, double y_prev, double u, double u_prev, double a, double b, double c, double d) {
	return a * y - b * y_prev * y_prev + c * u + d * sin(u_prev);
}

int main() {
	setlocale(LC_ALL,"RU");
	double a, b, c, d;
	double y0, u0;
	int n;

	cout << "Введите константы a, b, c, d: ";
	cin >> a >> b >> c >> d;

	cout << "Введите начальное значение температуры y(0): ";
	cin >> y0;

	cout << "Введите начальное значение теплоты u(0): ";
	cin >> u0;

	cout << "Введите число шагов: ";
	cin >> n;

	double y_linear = y0;
	double y_nonlinear = y0;
	double u = u0;

	cout << "Шаги\tЛинейная модель\tНелинейная модель\n";

	for (int step = 1; step <= n; ++step) {
		double linear_result = linearModel(y_linear, u, a, b);
		double nonlinear_result = nonlinearModel(y_nonlinear, y_nonlinear, u, u, a, b, c, d);

		cout << step << "\t" << linear_result << "\t\t" << nonlinear_result << "\n";

		y_linear = linear_result;
		y_nonlinear = nonlinear_result;
	}

	return 0;
}
