#include  <iostream>
#include  <cmath>

using  namespace  std;

double linear(double  y, double  u, double  a, double  b)
{
	return  a * y + b * u;
}
double nonlinear(double  y, double  u, double  a, double  b, double  c, double  d)
{
	return  a * y - b * y * y + c * u + d * sin(u);
}
int  main()
{
	setlocale(LC_ALL, "Russian");
	double  y, u, a, b, c, d;
	cout << "Введите y, u = ";
	cin >> y >> u;
	cout << "Введите а, b, c, d = ";
	cin >> a >> b >> c >> d;
	int  n;
	cout << "Введите n = ";
	cin >> n;
	double  y1 = y, y2 = y;
	for (int i = 0; i < n; i++)
	{
		y1 = linear(y1, u, a, b);
		y2 = nonlinear(y2, u, a, b, c, d);
		cout << "Шаг " << i + 1 << ", линейная y = " << y1 << ", нелинейная y = " << y2 << endl;
	}
	return  0;
}