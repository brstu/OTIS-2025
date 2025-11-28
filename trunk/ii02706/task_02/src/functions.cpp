#include "functions.h"
using namespace std;

void liner_funcnt(double& y1)
{
	y1 = first_funct_const * y1 + second_funct_const * third_funct_const;
}

void nonliner_funct(double& y2, double& y_previous, bool& second_iteration)
{
	const double fourth_funct_const = 0.4;
	const double fifth_funct_const = 0.5;
	if (second_iteration)
	{
		y_previous = y2;
		y2 = first_funct_const * y2 + fourth_funct_const * third_funct_const + fourth_funct_const * sin(third_funct_const); 
		second_iteration = false;
	}
	else
	{
		double buf;
		buf = first_funct_const * y2 - second_funct_const * pow(y_previous, 2) + fourth_funct_const * third_funct_const + fifth_funct_const * sin(third_funct_const);
		y_previous = y2;
		y2 = buf;
	}
}