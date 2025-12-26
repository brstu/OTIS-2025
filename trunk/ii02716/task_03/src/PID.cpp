#include "PID.h"
using namespace std;

void PID(double val) {
	Constunts con = { 0.85,0.05,1.5,1.2,1.4,1.6 };
	double err;
	double u;
	double y;
	Equations e(2.3, 4.5, 0.0, 5.7);
	e.Qs_calcul(con);
	e.SetW(val);
	for (int i = 0; i < 200; i++) {
		e.E_calcul(i);
		err = e.Get_E(i);
		std::cout << "Error on iteration " << i << " = " << err << std::endl;
		e.U_calcul(i);
		u = e.GetU();
		std::cout << "U on iteration " << i << " = " << u << std::endl;
		e.LinearModel(con);
		y = e.GetY();
		std::cout << "Y on iteration " << i << " = " << y << std::endl;
		if (!e.chek()) {
			e.SetDelt_U(10);
		}
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
	}
}

