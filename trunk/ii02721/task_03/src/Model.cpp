#include "Model.h"

void Models::calcul_err(int place){
e.resize(500,0);
e[place] = w - y_prev;
}
void Models::calcul_Q(Qs &q,const Constants &con){
q.q0 = con.k * (1 + con.Td/con.To);
q.q1 = -con.k * (1 + 2 * con.Td/con.To - con.To/con.T);
q.q2 = con.k * con.Td/con.To;
}
void Models::calcul_u(const Qs &q,int place){
if(place > 2){
 delt_u = q.q0 * e[place] + q.q1 * e[place - 1] + q.q2 * e[place - 2];
}
else{
delt_u = q.q0 * e[place];
}
u = u_prev + delt_u;
u_prev = u;
}
void Models::linear(const Constants &con){
y = con.a * y_prev + con.b * u;
y_prev = y;
}

bool Models::compare() const{
return w > y_prev;
}

void Models::SetDelt(double val){
delt_u = val;
}
double Models::GetE(int place) const{
return e[place];
}
double Models::GetY() const{
return y;
}
double Models::GetU() const{
return u;
}

