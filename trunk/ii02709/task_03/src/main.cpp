#include "pid_controller.h"
#include "model.h"
#include <iostream>
#include <iomanip>

int main()
{
    constexpr double dt = 0.1;
    constexpr int steps = 2000;

    PIDController pid(10.0, 1.0, 0.8, dt);  // Работает идеально
    Model plant(0.1, 1.0, 0.0, dt);

    double setpoint = 1.0;
    std::cout << std::fixed << std::setprecision(6);

    for (int k = 0; k < steps; ++k) {
        double y = plant.getTemperature();
        double e = setpoint - y;
        double u = pid.compute(e);
        plant.update(u);

        std::cout << k*dt << "\t" << y << "\t" << u << "\t" << e << "\n";
    }
}