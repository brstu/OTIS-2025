#include <iostream>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");

	const int steps = 10;
	double y[steps];
	double u[steps];
	double a, b, c, d;

	cout << "Рассчет по линейной модели\n";
	cout << "Введите коэффициент a: ";
	cin >> a;
	cout << "Введите коэффициент b: ";
	cin >> b;
	cout << "Введите начальную температуру объекта y(0): ";
	cin >> y[0];
	cout << "Введите начальную температуру объекта u(0): ";
	cin >> u[0];

	for (int i = 1; i < steps; i++) 
	{
		y[i] = a * y[i - 1] + b * u[i - 1];
		u[i] = u[i - 1] * 0.8;
		cout << "y[" << i << "] = " << y[i] << endl;
	}
	
	cout << "Рассчет по нелинейной модели\n";
	cout << "Введите коэффициент a: ";
	cin >> a;
	cout << "Введите коэффициент b: ";
	cin >> b;
	cout << "Введите коэффициент c: ";
	cin >> c;
	cout << "Введите коэффициент d: ";
	cin >> d;
	cout << "Введите начальную температуру объекта y(0): ";
	cin >> y[0];
	cout << "Введите следующую температуру объекта y(1): ";
	cin >> y[1];
	cout << "Введите начальную температуру объекта u: ";
	cin >> u[0];
	u[1] = u[0] * 0.8;

	for (int i = 1; i < steps - 1; i++)
	{
		y[i + 1] = a * y[i] - b * y[i - 1] / 2.0 + c * u[i] + d * sin(u[i - 1]);
		u[i + 1] = u[i] * 0.8;
		cout << "y[" << i << "] = " << y[i] << endl;
	}
}

