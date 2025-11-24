#include <iostream>
#include "pid.h"
#include "models.h"

int main() {
    double y = 0.0, y_prev = 0.0;
    double u_prev = 0.0;

    PID pid(0.5, 2.0, 0.3, 0.1); 
    double w = 1.0;

    for (int k = 0; k < 200; ++k) { 
        double e = w - y;
        double u = pid.update(e);

        y = non_linear_model(y, y_prev, u, u_prev,
                             1.0, 0.05, 0.2, 0.1);

        std::cout << k << "\t" << y << "\t" << u << std::endl;
    }

    return 0;
}
