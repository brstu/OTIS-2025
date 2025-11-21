#ifndef PID
#define PID
#include <iostream>
#include <vector>
#include "../src/Class.h"


class PID : public Obj {
private:
	std::vector<double> e;
	std::vector<double> yP;
	std::vector<double> w;//öåëåâîå çíà÷åíèå
	std::vector<double> u;
	std::vector<double> deltU;
	double Td;//ïîñòîÿííàÿ äåôô
	double To;//øàã ïî êâàíòó
	double T;//øàã
	double q0;
	double q1;
	double q2;
	double k;//êýô ïåðåäà÷è
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
