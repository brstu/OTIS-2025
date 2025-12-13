#include <iostream>
#include <vector>
#include "Linear.h"

using namespace std;


int main()
{
	int k;
	vector<double> y;
	vector<double> u;
	double a = 1;
	double b = 1;
	input(k, u, y, a, b);
	for (int i = 0; i < k; i++) {
		linear(i, k, y, u, b, a);
	}
	for (auto n : y) {
		cout << n << endl;
	}
	return 0;
}
