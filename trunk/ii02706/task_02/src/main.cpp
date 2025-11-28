#include "functions.h"

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double y1;
	double y2;
	double y_previous;
	bool second_iteration = true;
	cout << "Введите вашу термепаруту: ";
	cin >> y1;
	y2 = y1;
	int n = 20;
	cout << "Линейная модель\n" << y1 << endl;
	for (int i = 0; i < n; i++)
	{
        liner_funcnt(y1);
		cout << y1 << endl;
	}
	cout << endl << "Квадратичная модель\n" << y2 << endl;
	for (int i = 0; i < n; i++)
	{
		nonliner_funct(y2, y_previous, second_iteration);
		cout << y2 << endl;
	}
}