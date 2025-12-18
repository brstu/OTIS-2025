#ifndef PID_H
#define PID_H
#include <vector>
/**
 * \brief Class for imitation of PID
 *
 */
class PID {
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
* \brief Constructor to get variables from user
*/
	PID();
/**
* \brief Constructor to set variables
* Used in tests
*/
	PID(double T, double To, double Td, double k);
/**
* \brief Function for calculating q0 q1 q2
* \param Variable place used for loop
*/
	void Qs();
/**
* \brief Function for calculating error E
* \param Variable place used for loop
*/
	void E(int place);
	void U(int place);
/**
* \brief Function for linear model
* \param Variable place used for loop
*/
	void lin(int place);
/**
* \brief Main function which imitates PID regulator
*/
	void Model();
	/**
	* \brief Function to get Qs
	* uses in tests
	*/
	void GetQ(double& val, double& val1, double& val2) const;
	/**
	* \brief Function for assignments constants
	*/
	void init();
};
#endif 

