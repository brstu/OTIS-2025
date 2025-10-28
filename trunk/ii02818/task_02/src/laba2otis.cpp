#include "lab2otis.h"

TemperatureModel::TemperatureModel(double a, double b, double c, double d) 
    : a(a), b(b), c(c), d(d), y_curr(0), y_prev(0), u_curr(0), u_prev(0) {}

void TemperatureModel::setInitialState(double y0, double y1, double u0, double u1) {
    y_prev = y0;
    y_curr = y1;
    u_prev = u0;
    u_curr = u1;
}

void TemperatureModel::updateControl(double u_new) {
    u_prev = u_curr;
    u_curr = u_new;
}

std::vector<double> TemperatureModel::simulateLinear(int time_steps) {
    std::vector<double> temperatures(time_steps);
    
    if(time_steps >= 1) temperatures[0] = y_prev;
    if(time_steps >= 2) temperatures[1] = y_curr;
    
    for(int τ = 2; τ < time_steps; τ++) {
        temperatures[τ] = a * temperatures[τ-1] + b * u_curr;
    }
    
    return temperatures;
}

std::vector<double> TemperatureModel::simulateNonlinear(int time_steps) {
    std::vector<double> temperatures(time_steps);
    
    if(time_steps >= 1) temperatures[0] = y_prev;
    if(time_steps >= 2) temperatures[1] = y_curr;
    
    for(int τ = 2; τ < time_steps; τ++) {
        temperatures[τ] = a * temperatures[τ-1] 
                        - b * std::pow(temperatures[τ-2], 2) 
                        + c * u_curr 
                        + d * std::sin(u_prev);
    }
    
    return temperatures;
}