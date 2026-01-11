#ifndef VARIABLES_H
#define VARIABLES_H

struct Qs {
	double q0;
	double q1;
	double q2;
	Qs(double q0_val, double q1_val, double q2_val) :
		q0(q0_val), q1(q1_val), q2(q2_val) {
	}
};
struct Const_ {
	double T;
	double Td;
	double To;
	double k;
	double a;
	double b;

	Const_(double T_val, double Td_val, double To_val, double k_val, double a_val, double b_val) :
		T(T_val), Td(Td_val), To(To_val), k(k_val), a(a_val), b(b_val) {
	}
};

#endif 

