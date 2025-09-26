#include  <iostream>
#include  <cmath>
using  namespace  std;

double lin(double  y, double  u, double  a, double  b)
{

	return a * y + b * u;
}

double nonlin(double& y0, double& y1, double u, double a, double b, double c, double d)
{
	y0 = y1;
	y1 = a * y1 - b * pow(y0, 2) + c * u + d * sin(u);
	return y1;
}

int  main()
{
	setlocale(LC_ALL, "RUS");
	double  y = 0,
		u = 0,
		a = 0,
		b = 0,
		c = 0,
		d = 0;

	int  n = 0;

	cout << "������� �������� ����������� (y): ";
	cin >> y;
	cout << "������� �������� ������� (u): ";
	cin >> u;
	double y0 = 0,
		y1 = y,
		y2 = 0;
	cout << "������� ��������� �, b, c, d: ";
	cin >> a >> b >> c >> d;

	cout << "������� ���-�� �����: ";
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		y = lin(y, u, a, b);
		y2 = nonlin(y0,y1,u,a, b, c, d);
		cout << "��� " << i
			<< ", ����������� �������� �����. = "<< y
			<< ",����������� ���������� �����. = " << y2 << endl;
	}

	return  0;
}