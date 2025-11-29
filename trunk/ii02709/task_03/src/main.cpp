/**
 * @file main.cpp
 * @brief Консольный симулятор ПИД-регулятора. Выводит CSV-данные.
 */

#include <iostream>
#include <iomanip>
#include "pid.h"
#include "plant.h"

int main() {
    const double T0 = 0.1;
    const int steps = 1000;
    const double setpoint = 50.0;

    LinearPlant plant(0.98, 0.05, 0.0, 0.0);
    PID pid(10.0, 0.1, 0.01, T0);

    std::cout << "t,setpoint,y,u,e\n";

    double t = 0.0;
    for (int k=0; k<steps; ++k) {
        double y = plant.y();
        double e = setpoint - y;
        double u = pid.update(e);
        plant.step(u);

        std::cout << std::fixed << std::setprecision(3)
                  << t << "," << setpoint << "," << plant.y()
                  << "," << u << "," << e << "\n";

        t += T0;
    }

    return 0;
}
