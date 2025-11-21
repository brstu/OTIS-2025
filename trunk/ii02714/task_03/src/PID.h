#include <iostream>
#include <vector>
#include "C:\Users\Boss\Desktop\OTIS-2025\trunk\ii02714\task_03\src\linaer.h"
#include "C:\Users\Boss\Desktop\OTIS-2025\trunk\ii02714\task_03\src\Class.h"


class PID : public Obj {
private:
	std::vector<double> e;
	std::vector<double> yP;
	std::vector<double> w;//целевое значение
	std::vector<double> u;
	std::vector<double> deltU;
	double Td;//постоянная дефф
	double To;//шаг по кванту
	double T;//шаг
	double q0;
	double q1;
	double q2;
	double k;//кэф передачи
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