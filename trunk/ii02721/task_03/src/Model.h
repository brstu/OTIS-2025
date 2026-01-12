#ifndef MODEL_H
#define MODEL_H
#include <vector>
/**
*\brief Struct for constants
 
*/
struct Constants
{
	double a;
	double b;
	double k;
	double To;
	double T;
	double Td;

	Constants(double a_, double b_, double k_, double To_, double T_, double Td_)
        : a(a_), b(b_), k(k_), To(To_), T(T_), Td(Td_) {}
};
/**
*\brief Struct for resalt of Qs
*/
struct Qs{
	double q0;
	double q1;
	double q2;

	 Qs(double q0_, double q1_, double q2_) : q0(q0_), q1(q1_), q2(q2_) {}
};
/**
*\brief  Class consist of method for PID
*/
class Models{
private:
	std::vector<double> e;
	double y_prev;
	double u_prev;
	double delt_u;
	double w; 
	double y;
	double u;
public:
/**
*\brief Constructor for init variables 
*/
	Models(double y_prev_val,double u_prev_val,double delt_u_val,double w_val,double u_val,double y_val)
	:y_prev(y_prev_val),u_prev(u_prev_val),delt_u(delt_u_val),w(w_val),y(y_val),u(u_val){}
/**
*\brief Calculating error
*/ 
	void calcul_err(int place);
/**
*\brief Calculating Q
*/
	void calcul_Q(Qs &q,const Constants &con) const;
/**
*\ brief Calculating Qs
*/
	void calcul_u(const Qs &q,int place);
/**
*\brief Imitation of linear model
*/
	void linear(const Constants &con);
/**
*\brief Uses for comoaring w and y
*return true or false
*/
	bool compare() const;
	void SetDelt(double val);
	double GetE(int place) const;
	double GetY() const;
	double GetU() const;
};


#endif
