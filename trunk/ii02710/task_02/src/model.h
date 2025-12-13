#ifndef MODEL_H
#define MODEL_H

// Функция для одного шага линейной системы
double linearStep(double a, double b, double u, double y_prev);

// Функция для одного шага нелинейной системы
double nonlinearStep(double a, double b, double c, double d,
    double y_curr, double y_prev, double u_curr, double u_prev);

#endif