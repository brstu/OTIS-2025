#ifndef PID_H
#define PID_H
#include <vector>

struct Arg {
	std::vector<double> y;
	std::vector<double> u;
	std::vector<double> e;
	std::vector<double> delt_u;
	double a;
	double b;
	double w;
	double maxT;
};
struct Qs
{
	double k;
	double To;
	double Td;
	double T;
	double q0;
	double q1;
	double q2;
};
/**
* \brief Function for linear model
* \param Arg& g struct where all variables located
* \param place used for loop
*/
void linearMod(Arg& g, const int& place);
/**
* \brief Function for calculating error E
* \param Arg& g struct where all variables located
* \param place used for loop
*/
void E(Arg& g, const int& place);
/**
* \brief Function for calculating q0 q1 q2
* \param Qs& q struct where all variables located
*/
void findQ(Qs& q);
/**
* \brief Function for calculating u & delt_u
* \param Qs& q struct where all variables located
* \param Arg& g struct where all variables located
* \param place used for loop
*/
void findU(Qs& q,Arg& g, const int& place);
/**
* \brief Function for decreasing q when temperature higher than needed
* \param Qs& q struct where all variables located
*/
void ReqQ(Qs& q);
/**
* \brief Main function which imitates PID regulator
* \param Qs& q struct where all variables located
*/
void PID(Qs& q, Arg& g);

#endif 

