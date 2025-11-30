#include <iostream>
#include <cmath>
#include "functions.h"

using namespace std;

int main()
{
	double y;
    double u;
    double a;
    double b;
    double c;
    double d;
	cout << "y, u = ";
	cin >> y >> u;
	cout << "а, b, c, d = ";
	cin >> a >> b >> c >> d;

	int n;
	cout << "n = ";
	cin >> n;

	double y1 = y;
 double y2 = y;
	for (int i = 0; i < n; i++)
	{
 y1 = linear(y1, u, a, b);
		y2 = nonlinear(y2, u, a, b, c, d);
		cout << "Step " << i+1 << ", linear y = " << y1 << ", n-linear y = " << y2 << endl;
	}

	return 0;
}