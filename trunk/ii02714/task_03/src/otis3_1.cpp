#include <iostream>
#include <vector>
#include "PID.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	PID p;
	p.calcul_PID(0);
	return 0;
}
