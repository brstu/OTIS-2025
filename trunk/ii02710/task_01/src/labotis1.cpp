#include <iostream>
#include <cmath>

int main() {
    std::cout << "First system - Linear" << std::endl;
    const double a = 0.4; // Coefficient for previous output (y)
    const double b = 0.3; // Coefficient for input (u)
    const int n = 15; // Simulation time steps
    double u = 0.5; // Step size for input signal increment
    double y_current = 0; // Initialize y_current value
    
    for (int tau = 0; tau < n; tau++) {
        y_current = a * y_current + b * u;
        std::cout << "y[" << tau + 1 << "] = " << y_current << std::endl;
    }
    std::cout << std::endl;

    std::cout << "\nSecond system - Nonlinear" << std::endl;
    const double a2 = 0.5; // Coefficient for previous output (y)
    const double b2 = 0.2; // Nonlinear coefficient for squared previous output (prevY²)
    const double c2 = 0.1; // Linear coefficient for input (u)
    const double d2 = 0.3; // Nonlinear coefficient for sinusoidal input term
    
    double u_prev = 1.0; // Step size for input signal previous increment ( u[tau-1] )
    double u_curr = 2.0; // Step size for input signal current increment ( u[tau] )
    
    double y_prev = 25.0; // y[tau-1]
    double y_curr = 26.0; // y[tau]
    double y_next;        // y[tau+1]

    const double u_offset = 0.3;
    
    for (int tau = 1; tau < n; tau++) {
        y_next = a2 * y_curr - b2 * (y_prev * y_prev) + c2 * u_curr + d2 * std::sin(u_prev);
        
        std::cout << "y[" << tau + 1 << "] = " << y_next << '\n';
        
        // Update for next iteration
        y_prev = y_curr;
        y_curr = y_next;
        
        // Update u values (using example sequence)
        u_prev = u_curr;
        u_curr += u_offset;
    }

    return 0;
}