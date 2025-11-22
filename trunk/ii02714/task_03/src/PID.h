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
	void SetY(int place, double data) override;
	void setE(int place);
	void SetQs();
	void SetU(int place) override;
	int iterGet();
	double GetE(int place) const;
	double GetYp(int place) const;
	double GetUP(int place) const;
	void SetW(int place, double data);
	double GetQs0() const;
	double GetQs1() const;
	double GetQs2() const;

};
#endif
