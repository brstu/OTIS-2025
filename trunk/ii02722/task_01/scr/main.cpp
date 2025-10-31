﻿#include<iostream>
using namespace std;

float a = 0.5,
	b = 0.2,
	c = 0.15,
	d = 0.3,
	u = 1.2;
int main()
{
	float y0, y1, y2 ,y_temp;
	cout << "y1 = ?";
	cin >> y_temp;
	y1 = y_temp;
	y0 = y1;
	int n = 10;
	cout << endl << "Linear"<<endl;
	for (int i = 0; i < n; i++)
	{
		cout << "t" << i + 1 << " = ";
		y2 = a * y1 + b * u;
		cout << y2 << endl;
		y0 = y1;
		y1 = y2;
	}

	cout << endl << "Nonlinear:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "t" << i + 1 << " = ";
		y2 = a * y1 - b * y0 * y0 + c * u + d * sin(u);
		cout << y2 << endl;
		y0 = y1;
		y1 = y2;
	}

}