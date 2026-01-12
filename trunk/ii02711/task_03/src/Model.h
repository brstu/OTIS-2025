#ifndef PID_H
#define PID_H
#include <vector>
/**
* \brief Class which imitate PID with help of functions
*/
class PID_reg {
private:
	std::vector<double> e;
	std::vector<double> y;
	std::vector<double> u;
	std::vector<double> d_u;
	double T;
	double To;
	double Td;
	double k;
	double q0;
	double q1;
	double q2;
	double w;
	double max;
	double a;
	double b;
public:
	/**
     *\brief Constructor for init variables
	*/
	PID_reg();
	/**
	 * \brief Function which calculates Qs
	*/
	void Qs_find();
	/**
	 * \brief Function which calculates E
	*/
	void E_find(int place);
	/**
	*  \brief Function which calculates U n delt_U
	*/
	void U_find(int place);
	/**
	*  \brief Function which calculates linear equation
	*/
	void lin(int place);
	/**
	*  \brief Imitation of PID regulator
	*/
	void Imitation();
	/**
	* \brief Function used in tests to chek result of Qs_find() function
	*/
	void GetQ(double& val, double& val1, double& val2) const;
	/**
	*  \brief Function which init all constants used in programm 
	*/
	void init();
};
#endif 

