#ifndef LINE_H
#define LINE_H
#include <iostream>
#include <vector>

struct Params
{
	int k;
	std::vector<double> y;
	std::vector<double> u;
	double a;
	double b;
};

void input(Params &s);
void linear(Params &s, const int& place);

#endif
