#include <iostream>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");

	const int steps = 10;
	double y[steps];
	double u[steps];
	double a, b, c, d;

	cout << "������� �� �������� ������\n";
	cout << "������� ����������� a: ";
	cin >> a;
	cout << "������� ����������� b: ";
	cin >> b;
	cout << "������� ��������� ����������� ������� y(0): ";
	cin >> y[0];
	cout << "������� ��������� ����������� ������� u(0): ";
	cin >> u[0];

	for (int i = 1; i < steps; i++) 
	{
		y[i] = a * y[i - 1] + b * u[i - 1];
		u[i] = u[i - 1] * 0.8;
		cout << "y[" << i << "] = " << y[i] << endl;
	}
	
	cout << "������� �� ���������� ������\n";
	cout << "������� ����������� a: ";
	cin >> a;
	cout << "������� ����������� b: ";
	cin >> b;
	cout << "������� ����������� c: ";
	cin >> c;
	cout << "������� ����������� d: ";
	cin >> d;
	cout << "������� ��������� ����������� ������� y(0): ";
	cin >> y[0];
	cout << "������� ��������� ����������� ������� y(1): ";
	cin >> y[1];
	cout << "������� ��������� ����������� ������� u: ";
	cin >> u[0];
	u[1] = u[0] * 0.8;

	for (int i = 1; i < steps - 1; i++)
	{
		y[i + 1] = a * y[i] - b * y[i - 1] / 2.0 + c * u[i] + d * sin(u[i - 1]);
		u[i + 1] = u[i] * 0.8;
		cout << "y[" << i << "] = " << y[i] << endl;
	}
}

