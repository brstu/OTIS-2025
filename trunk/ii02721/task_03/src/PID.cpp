#include "PID.h"

void PID_model(double desired_temp,double start){
Models m(start,0.0,0.0,desired_temp);
Constants con(0.85,0.05,1.2,1.3,1.3,1.3);
Qs q(0.0,0.0,0.0);
m.calcul_Q(q,con);
for(int i = 0;i < 200;i++){
m.calcul_err(i);
double err = m.GetE(i);
std::cout << "Error = " << err << std::endl;
m.calcul_u(q,i);
double u = m.GetU();
std::cout << "U = " << u << std::endl;
m.linear(con);
double y = m.GetY();
std::cout << "Y = " << y << std::endl;
if(!m.compare()){
m.SetDelt(15.0);
	} 
			}

}
