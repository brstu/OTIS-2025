#include <iostream>
#include <vector>  
#include "model.h"

using namespace std;

int main() {
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    double initial_y = 23;
    
    LinearModel linear_model(a, b, initial_y);
    NonlinearModel nonlinear_model(a, b, c, d, initial_y);
    
   
    std::vector<double> u = { 10, 15, 20, 25, 30, 25, 20, 15, 10, 5 };
    
    
    const size_t steps = u.size();
    
    cout << "Model :" << endl;
    cout << "Time\tu\tLinear\tNonlinear" << endl;
    cout << "0\t0\t" << initial_y << "\t" << initial_y << endl;
    
    for (size_t i = 0; i < steps; i++) {
        double power = u[i];
        double y_linear = linear_model.calculate(power);
        double y_nonlinear = nonlinear_model.calculate(power);
        cout << i + 1 << "\t" << power << "\t" << y_linear << "\t" << y_nonlinear << endl;
    }
    
    return 0;
}