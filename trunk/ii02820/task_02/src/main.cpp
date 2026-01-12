#include <iostream>
#include <cmath>
#include "model.h"
#include <vector>
#include <array>

using namespace std;

int main() {
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    double initial_y = 23;
    
    // Используем std::array вместо C-style массива
    std::array<double, 10> u = { 10, 15, 20, 25, 30, 25, 20, 15, 10, 5 };
    
    int steps = 10;
    cout << "Model Comparison:" << endl;
    cout << "Time\tu\tLinear\tNonlinear" << endl;
    
    double y_linear = initial_y;
    double y_nonlinear_prev = initial_y;
    double y_nonlinear_current = initial_y;
    
    cout << "0\t0\t" << initial_y << "\t" << initial_y << endl;
    
    for (int i = 0; i < steps; i++) {
        double power = u[i];
        
        y_linear = linear(y_linear, power, a, b);
        double new_y_nonlinear = non_linear(
            y_nonlinear_current, 
            y_nonlinear_prev, 
            power, 
            a, b, c, d
        );
        
        y_nonlinear_prev = y_nonlinear_current;
        y_nonlinear_current = new_y_nonlinear;
        
        cout << i + 1 << "\t" << power << "\t" 
             << y_linear << "\t" << y_nonlinear_current << endl;
    }
    
    return 0;
}