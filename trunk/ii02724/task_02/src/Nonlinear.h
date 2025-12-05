#ifndef NONLINEAR_H
#define NONLINEAR_H
struct Constant {
	double param_a;
	double param_b;
	double param_c;
	double param_d;
};
void Nonlinear(Constant &c, int steps_count, double& current_temp, double current_heat, double next_temp, double previous_temp, double previous_heat);

#endif 
