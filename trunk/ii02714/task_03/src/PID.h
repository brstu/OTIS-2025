#ifndef PID_H
#define PID_H
#include <iostream>
#include <vector>
#include "../src/Class.h"


class PID : public Obj {
private:
	std::vector<double> e;
	std::vector<double> yP;
	std::vector<double> w;
	std::vector<double> u;
	std::vector<double> deltU;
	double Td;
	double To;
	double T;
	double q0;
	double q1;
	double q2;
	double k;
	int iter;
public:
	PID(double data, double data2);
	PID();
	void SetW();
	void SetY(int place);
	void SetY(int place, double data);
	void setE(int place);
	void SetQs();
	void SetU(int place);
	int iterGet();
	double GetE(int place);
	double GetYp(int place);
	double GetUP(int place);
	void SetW(int place, double data);
	double GetQs0();
	double GetQs1();
	double GetQs2();

};
#endif
