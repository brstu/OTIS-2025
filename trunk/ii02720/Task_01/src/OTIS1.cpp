#include <iostream>
#include <cmath>
#include <array>

using namespace std;

class TemperatureModel {
private:
    double a;
    double b;
    double c; 
    double d;
    double y_prev;
    double y_prev2;
    double u_prev{0};

public:
    TemperatureModel(double a_val, double b_val, double c_val, double d_val, double Y0) 
        : a(a_val), b(b_val), c(c_val), d(d_val), y_prev(Y0), y_prev2(Y0)
{
}

    double linear_step(double u) {
        double y = a * y_prev + b * u;
        y_prev = y;
        return y;
    }

    double nonlinear_step(double u) {
        double y = a * y_prev - b * y_prev2 * y_prev2 + c * u + d * sin(u_prev);
        y_prev2 = y_prev;
        y_prev = y;
        u_prev = u;
        return y;
    }
};

int main() {
    double a = 0.8;
    double b_linear = 0.3;
    double b_nonlinear = 0.01;
    double c = 0.4;
    double d = 0.1;
    double Y0 = 20.0;
    
    std::array<double, 10> u = {2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.0};
    int n = 10;
    
    TemperatureModel linear_model(a, b_linear, 0, 0, Y0);
    TemperatureModel nonlinear_model(a, b_nonlinear, c, d, Y0);
    
    cout << "Time\tLinear\tNonlinear" << endl;
    
    for (int tau = 0; tau < n; tau++) {
        double y_linear = linear_model.linear_step(u[tau]);
        double y_nonlinear = nonlinear_model.nonlinear_step(u[tau]);
        
        cout << tau << "\t" << y_linear << "\t" << y_nonlinear << endl;
    }
    
    return 0;
}