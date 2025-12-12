#include "functions.h"

void liner_funct(double& y1)
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
		second_iteration = false;
	}

}
    