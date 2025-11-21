#ifndef LINEAR
#define LINEAR
#include "Class.H"

void Obj::input();
void Obj::linear(const int& place);
void Obj::nonlinear(const int& place);
int Obj::getN() const;
double Obj::getY(int place) const;
void Obj::SetU(int place,double data);
void Obj::SetY(int place, double data);
#endif LIANEAR

