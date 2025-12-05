#ifndef LIN_H
#define LIN_H
#include <iostream>
struct Nonl {
	double A;
	double B;
	double C;
	double D;
	double temp_now;
	double heat_now;
	double temp_prev;
	double heat_prev;
};
double linear(double a,double b,double temp_prev,double heat_now);
double nonlinear(const Nonl &l);

#endif 
