#ifndef EQUATION_H
#define EQUATION_H
#include <vector>
/**
* \brief Struct with constants
*/
struct Constunts
{
	double a;
	double b;
	double T;
	double To;
	double Td;
	double k;

};
/**
* \brief CLass consist of equations used in PID regulator
*/
class Equations {
private:
	std::vector<double> e;
	double q0;
	double q1;
	double q2;
	double u;
	double f_u;
	double y_prev;
	double y;
	double delt_u;
	double w;
public:
/**
* \brief Constructor for init variables used in equations
*/
	Equations(double u_val, double y_prev_val, double delt_u_val,double w_val) :
		u(u_val), y_prev(y_prev_val), delt_u(delt_u_val), w(w_val) {
		e.resize(500, 0);
	}
	/**
	* \brief Imitation of linear model
	* \param const Constunts& k is struct with all constants
	*/
	void LinearModel(const Constunts& k);
	/**
	* \brief Calculating of U and delta_U
	* \param place uses for controlling outrange of vector
	*/
	void U_calcul(int place);
	/**
	* \brief Calculates q0 q1 q2
	* \param const Constunts& k is struct with all constants
	*/
	void Qs_calcul(const Constunts& c);
	/**
	* \brief Calculates error e
	* \param place uses for controlling outrange of vector
	*/
	void E_calcul(int place);
	double GetY() const;
	double GetU() const;
	void SetDelt_U(double val);
	double Get_E(int place) const;
	/**
	* \brief Checking if temperature already have reached necessary temp
	* return true if reached and false if not
	*/
	bool chek();
	void SetW(double w);
};


#endif 

