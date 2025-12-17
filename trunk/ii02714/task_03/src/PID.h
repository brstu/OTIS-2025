#ifndef PID_H
#define PID_H 
#include <iostream>
#include <vector>
#include <cstdlib>
/**
* \brief Class for implementing a PID controller
*/
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
/**
* \brief Constructor for instantiating variables and vectors
*/
	PID();
/**
* \brief A linear function of the form: y[t] = a * y[t - 1] + b * u[t - 1]
* \param place is used to determine the temperature at a certain moment
*/
	void linear(int place);
/**
*\brief Function for calculating delta_u[place] delta_u variable needed to calculate U
* \param place is used to determine the temperature at a specific moment
*/
	void calcul_DeltU(int place);
/**
* \brief Функция вычисления U
*  \param place служит для определения температуры в определнный момент
*/
	void calcul_U(int place);
/**
* \brief U calculation function
* \param place is used to determine the temperature at a specific moment
*/
	void calcul_q0_q1_q2();
/**
* \brief Calculate error function e
*/
	void calcul_e(int place);
/**
* \brief The main function that simulates the operation of the PID controller
* \param place is used to determine the temperature at a specific moment
*/
	void calcul_PID(int place);
/**
* \brief A function that adjusts the values ​​of constants a and b, decreasing them.
* \param val is the value by which a is divided.
*/
	void RegCoefs(double val);
/**
* \brief Function for getting the values ​​of q0, q1, q2
* Called in tests to check the program's operation
* \param val1 assigns the value to q0
* \param val2 assigns the value to q1
* \param val3 assigns the value to q2
*/
	void GetQs(double &val1,double &val2,double &val3) const;
};

#endif 

