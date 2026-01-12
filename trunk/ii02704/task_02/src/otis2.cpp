#include <iostream>
#include <vector>
#include "Linear.h"

using namespace std;


int main()
{
	Params p;
	input(p);
	for (int i = 0; i < p.k; i++) {
		linear(p,i);
	}
	for (auto n : p.y) {
		cout << n << endl;
	}
	return 0;
}
