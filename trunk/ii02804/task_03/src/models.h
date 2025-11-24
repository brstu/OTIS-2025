/// @file models.h
/// @brief Линейная и нелинейная функции 

#ifndef MODELS_H
#define MODELS_H

double linear_model(double y, double u, double a, double b);

double non_linear_model(double y, double& y_prev, double u, double& u_prev,
                        double a, double b, double c, double d);

#endif // MODELS_H
