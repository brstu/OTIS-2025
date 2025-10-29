#ifndef TEMPERATURE_MODEL_H
#define TEMPERATURE_MODEL_H

#include <vector>
#include <cmath>

class TemperatureModel {
private:
    double a;
    double b;
    double c; 
    double d;
    double y_curr =0;
    double y_prev =0;
    double u_curr =0;
    double u_prev =0;

public:
    TemperatureModel(double a, double b, double c, double d);
    void setInitialState(double y0, double y1, double u0, double u1);
    void updateControl(double u_new);
    const std::vector<double> simulateLinear(int time_steps);
    std::vector<double> simulateNonlinear(int time_steps);
    
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    double getD() const { return d; }
    double getCurrentY() const { return y_curr; }
    double getCurrentU() const { return u_curr; }
    double getPrevY() const { return y_prev; }
    double getPrevU() const { return u_prev; }
};

#endif