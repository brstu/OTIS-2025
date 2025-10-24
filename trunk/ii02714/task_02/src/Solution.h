#ifndef SOLUTION_H_TASK_02
#define SOLUTION_H_TASK_02
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Obj {
public:
	int k = 4;
	int t = 0;
	vector<double> y;
	vector<double> u;
	double y0 = 25;
	double a;
	double b;
	double c;
	double d;
	double c1;
	double rc;
	Obj();
	void input();
	void linear(const int& place);
	void nonlinear(const int& place);
	int getN() const;
	int getT() const;
	double getY(int place) const;
};


#endif SOLUTION_H_TASK_02
