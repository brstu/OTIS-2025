#include <iostream>
#include <cmath>
using namespace std;

void liner_funcnt(double& y1)
{
	double first_funct_const = 0.1;
	double second_funct_const = 0.2;
	double third_funct_const = 0.3;
	y1 = first_funct_const * y1 + second_funct_const * third_funct_const;
	cout << y1 << endl;
}

void quadro_funct(double& y2, double& y_previous, bool& first_iteration)
{
	double first_funct_const = 0.1;
	double second_funct_const = 0.2;
	double third_funct_const = 0.3;
	double fourth_funct_const = 0.4;
	double fifth_funct_const = 0.5;
	if (first_iteration)
	{
		y_previous = y2;
		y2 = first_funct_const * y2 + fourth_funct_const * third_funct_const + fourth_funct_const * sin(third_funct_const); 
		cout << y2 << endl;
		first_iteration = false;
	}
	else
	{
		double buf;
		buf = first_funct_const * y2 - second_funct_const * pow(y_previous, 2) + fourth_funct_const * third_funct_const + fifth_funct_const * sin(third_funct_const);
		y_previous = y2;
		y2 = buf;
		cout << y2 << endl;
	}
}


int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double y1, y2, y_previous;
	bool first_iteration = true;
	cout << "Введите вашу температуру: ";
	cin >> y1;
	y2 = y1;
	int n = 20;
	cout << "Линейная модель:\n" << y1 << endl;
	for (int i = 0; i < n; i++)
	{
    liner_funcnt(y1);
	}
	cout << endl << "Квадратичная модель:\n" << y2 << endl;
	for (int i = 0; i < n; i++)
	{
		quadro_funct(y2, y_previous, first_iteration);
	}
}