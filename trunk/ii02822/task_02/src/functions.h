#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class TemperatureModel {
public:
    static double linearModel(double y_prev, double u, double a, double b);
    static double nonlinearModel(double y_prev, double y_prev2, double u, double a, double b, double c, double d);
    static bool validateInput(double value);
    static bool validateSteps(int steps);
};

#endif