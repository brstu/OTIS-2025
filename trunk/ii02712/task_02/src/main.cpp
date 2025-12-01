#include <iostream>
#include <cmath>
#include "functions.h"

int main() {
    const int steps = 15;
    double y_next = 0;
    double y_pred;   
    double u = 1;  
    std::cout << "The Linear model" << std::endl;
    for (int i = 0; i < steps; i++) {
        y_next = linearModel(y_next, u);
        std::cout << i << "\t" << y_next << std::endl;
    }
    std::cout << std::endl;
    y_next = 0;
    double u_pred;  
    std::cout << "Nonlinear model:" << std::endl;
    for (int i = 0; i < steps; i++) {
        y_pred = y_next;
        u_pred = u;
        y_next = nonlinearModel(y_next, u, y_pred, u_pred);
        std::cout << i << "\t" << y_next << std::endl;
    }
    return 0;
}