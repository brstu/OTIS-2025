#ifndef PID_H
#define PID_H 
#include <iostream>
#include <vector>
#include <cstdlib>

class PID {
private:
	double q0;
	double q1;
	double q2;
	std::vector<double>deltU;
	std::vector<double>u;
	std::vector<double>y;
	std::vector<double>e;
	double w;
	double maxTemp;
	double k;
	double Td;
	double To;
	double T;
	double a;
	double b;
public:
	PID();
	void linear(int place);
	void calcul_DeltU(int place);
	void calcul_U(int place);
	void calcul_q0_q1_q2();
	void calcul_e(int place);
	void calcul_PID(int place);
	void RegCoefs(double val);
	void GetQs(double &val1,double &val2,double &val3) const;
};

#endif 

