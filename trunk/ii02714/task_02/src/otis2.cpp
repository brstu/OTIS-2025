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
		a.equation1(j);
		cout << "Temperature change at " << j << " is: " << a.getDelt() << endl;
	}
	t++;
	cout << "Nonlinear equation: Temperature at 1" << " equals: " << a.getY(0) << endl;
	for (int m = t; m < n; m++) {
		a.nonlinear(m);
		cout << "Nonlinear equation: Temperature at " << m + 1 << " equals: " << a.getY(m) << endl;
		a.equation1(m);
		cout << "Temperature change at " << m << " is: " << a.getDelt() << endl;
	}
	return 0;
}
