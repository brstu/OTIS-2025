#ifndef model_h
#define model_h

// Функция для одного шага линейной системы
double linearStep(double a, double b, double u, double y_prev);

struct NonLinearParams
{
    double a;
    double b;
    double c;
    double d;
};

// Функция для одного шага нелинейной системы
double nonlinearStep(const NonLinearParams &params,
    double y_curr, double y_prev, double u_curr, double u_prev);

#endif