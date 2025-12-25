#ifndef MODEL_H
#define MODEL_H

void modelInit(double K_obj = 1.0, double T_obj = 0.5);
double modelUpdate(double u, double dt);
void modelReset();
void modelSetParameters(double K_obj, double T_obj);

#endif