#include "functions.h"
#include <vector>
void liner_funcnt(double& y1)
{
	y1 = first_funct_const * y1 + second_funct_const * third_funct_const;
}

double nonliner_funct(double& y2, double& y_previous, bool& second_iteration)
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
    return y2;
}
std::vector<double> simulatePIDRegulatorByNonLinearModel(double w, int steps) {
    double y = 0.0; // Initial y
    double u = 0.0; // Initial u
    double y_prev = y - 0.1; // Init previous y (0.1 for difference)
    double u_prev = u - 0.1; // Init previous u (0.1 for difference)
    double e = w - y;
    double e_prev1 = e;
    double e_prev2 = e;
    std::vector<double> results;

    for (int k = 0; k < steps; k++) 
    {
        bool second_iteration = true;
        double u_new = u + q0 * e + q1 * e_prev1 + q2 * e_prev2;
        double y_new = nonliner_funct(y, u_new, second_iteration);
        double e_new = w - y_new;

        results.push_back(y_new);

        y_prev = y;
        u_prev = u;
        y = y_new;
        u = u_new;
        e_prev2 = e_prev1;
        e_prev1 = e;
        e = e_new;
    }

    return results;
}