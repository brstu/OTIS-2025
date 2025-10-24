#include "Solution.h"

int main()
{
	Obj a;
	a.input();
	int n = a.getN();
	int t = a.getT();
	for (int j = t; j < n; j++) {
		a.linear(j);
		cout << "Linear equation: Temperature at " << j + 1 << " equals: " << a.getY(j) << endl;
	}
	t++;
	cout << "Nonlinear equation: Temperature at 1" << " equals: " << a.getY(0) << endl;
	for (int m = t; m < n; m++) {
		a.nonlinear(m);
	}
	return 0;
}
