#ifndef SOLUTION_H_TASK_02
#define SOLUTION_H_TASK_02
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


class Obj {
private:
	int k = 4;
	int t = 0;
	vector<double> y;
	vector<double> u;
	double y0 = 25;
	double temp_change = 0;
	double a = 1;
	double b = 1;
	double c = 1;
	double d = 1;
	double c1 = 1;
	double rc = 1;
public:
	Obj();
	void input();
	void equation1(const int& place);
	void linear(const int& place);
	void nonlinear(const int& place);
	int getN() const;
	int getT() const;
	double getY(int place) const;
	double getDelt() const;
};


#endif SOLUTION_H_TASK_02
