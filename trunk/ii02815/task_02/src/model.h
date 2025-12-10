#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <string>

struct ModelParameters {
    double a;
    double b;
    double c;
    double d;
};

double linearModel(double y_current, double u_current, const ModelParameters& params);
double nonlinearModel(double y_current, double y_previous, double u_current, double u_previous, const ModelParameters& params);

void clearInput();
void readDouble(const std::string& text, double& value);
void readPositiveInt(const std::string& text, int& value);

#endif