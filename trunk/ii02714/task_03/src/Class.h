#ifndef CLASS
#define CLASS

#include <iostream>
#include <cmath>
#include <vector>
using std::cout;
using std::cin;
using std::vector;
class Obj {
private:
	int k = 4;
	int t = 0;
	vector<double> y;
	vector<double> u;
	double y0 = 25;
	double a = 1;
	double b = 1;
	double c = 1;
	double d = 1;
	double c1 = 1;
	double rc = 1;
public:
	Obj() {
		y.resize(k, 0);
		u.resize(k, 0);
	}
	void input();
	void linear(const int& place);
	void nonlinear(const int& place);
	int getN() const;
	int getT() const;
	double getY(int place) const;
	void SetY(int place,double data);
	void SetU(int place,double data);
};


#endif
