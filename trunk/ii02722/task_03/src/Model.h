#ifndef MODEL_H
#define MODEL_H
#include "Variables.h"
/*
* \brief Class with all formulas which uses PID regulator
* 
*/
class Model {
private:
	double y;
	double u;
	double u_d;
	double y_next;
	double u_next;
	double e;
	double e_past;
	double e_past2;
	double target;
	double max;
	bool condition;
public:
/*
* \brief Constructor of class.Allowa user to initialize variables
*
*/

	Model(double y_start, double u_, double u_d_, double y_n,
		double u_n, double e_, double e_p, double e_p2, double target_, double max_, bool condition_val)
		:y(y_start), u(u_), u_d(u_d_), y_next(y_n), u_next(u_n), e(e_), e_past(e_p), e_past2(e_p2), target(target_), max(max_), condition(condition_val)
	{}
	/*
	* \brief Function for calculating Error(e)
	*
	*/

	void find_e();

/*
* \brief Function for calculating U
* \params Qs q struct with value of qs
*/

	void find_u(const Qs& q);
/*
* \brief Function which imitates linear model 
* \params Const_& c struct with value of all constants
*/
	void lin(const Const_& c);
};
/*
* \brief Function for imitation PID regulator
* \params Qs q struct with value of qs
* Const_& c struct with value of all constants
*/
void PID_model(const Qs& q, const Const_& c);
/*
* \brief Function for calculating qs
* \params Qs q struct with value of qs
* Const_& c struct with value of all constants
*/
void find_Qs(Qs& q, const Const_& c);


#endif 

