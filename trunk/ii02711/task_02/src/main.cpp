#include <iostream>
#include <cmath>
#include "equations.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	Constant k;
	double a = 0.01;
	double b = 0.02;
	k.a = a;
	k.b = b;
	k.c = 0.03;
	k.d = 0.04;
	double y_next;
	double y;
	int t = 3;
	cout << "������� ��������� �������� Y ��� ���������: " << endl;
	cin >> y;
	for (int i = 1; i < t; i++) {
		double u;
		cout << "������� �������� U �� ��������: " << i << endl;
		cin >> u;
		double res = Linear(a, b, y, y_next, u);
		cout << "�������� ���������." << endl << "��������: " << i << endl << "���������: " << res << endl;
		y = y_next;
	}
	y = 0;
	double y_prev = 0;
	double u_prev = 0;
	y_next = 0;
	cout << endl;
	cout << "������� ��������� �������� Y ��� �����������: " << endl;
	cin >> y;
	for (int i = 1; i < t; i++) {
		double u;
		cout << "������� �������� U �� ��������: " << i << endl;
		cin >> u;
		double res = Nonlinear(k, y_prev, u, u_prev, y_next, y);
		cout << "���������� ���������." << endl << "��������: " << i << endl << "���������: " << res << endl;
		y_prev = y;
		u_prev = u;
		y = y_next;
	}
	return 0;
}