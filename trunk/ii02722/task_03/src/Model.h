#ifndef MODEL_H
#define MODEL_H
#include "Variables.h"

/*
* \brief Class with all formulas which uses PID regulator
* 
*/
class Model {
private:
	double u;
	double u_d;
	double y_next;
	double u_next;
	double e;
	double e_past;
	double e_past2;
	bool condition;
	double y;
	double target;
public:
	/*
	* \brief Struct uses to avoid big amout of params in function
	*/
	struct Params
	{
		double u;
		double u_d;
		double y_next;
		double u_next;
		double e;
		double e_past;
		double e_past2;
		Params(double u_val, double u_d_val, double y_n, double u_n, double e_val, double e_p,double e_p2) 
			:u(u_val), u_d(u_d_val), y_next(y_n), u_next(u_n), e(e_val), e_past(e_p), e_past2(e_p2) {
		}
	};
/*
* \brief Constructor of class. Allows user to initialize variables
*
*/
	Model(double y_start, double target_,bool condition_, const Params &p)
		:y(y_start), u(p.u),u_d(p.u_d), y_next(p.y_next), u_next(p.u_next), e(p.e), e_past(p.e_past), e_past2(p.e_past2), target(target_), condition(condition_)
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

