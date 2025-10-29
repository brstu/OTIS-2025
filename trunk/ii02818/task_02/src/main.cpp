#include <iostream>
#include "lab2otis.h"

int main() {
double a = 0.2;
    double b = 0.3;
    double c = 0.4;
    double d = 0.5;    
    TemperatureModel model(a, b, c, d);
    model.setInitialState(20.0, 21.0, 1.0, 1.5);
    
    int simulation_time;
    std::cout << "Enter simulation time steps: ";
    std::cin >> simulation_time;
    
    std::cout << "Model parameters: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
    
    std::cout << "\nLinear Model Simulation:" << std::endl;
    auto linear_results = model.simulateLinear(simulation_time);
    for(int t = 0; t < linear_results.size(); t++) {
        std::cout << "Time t=" << t << ": y(t) = " << linear_results[t] << std::endl;
    }
    
    std::cout << "\nNonlinear Model Simulation:" << std::endl;
    auto nonlinear_results = model.simulateNonlinear(simulation_time);
    for(int t = 0; t < nonlinear_results.size(); t++) {
        std::cout << "Time t=" << t << ": y(t) = " << nonlinear_results[t] << std::endl;
    }
    
    return 0;
}