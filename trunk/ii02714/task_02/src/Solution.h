#ifndef SOLUTION_H_TASK_02
#define SOLUTION_H_TASK_02
#include <iostream>
#include <cmath>
#include <vector>

class Obj {
public:
	int k = 4;
	int t = 0;
	std::vector<double> y;
	std::vector<double> u;
	double y0 = 25;
	double a = 1;
	double b = 1;
	double c = 1;
	double d = 1;
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


#endif
