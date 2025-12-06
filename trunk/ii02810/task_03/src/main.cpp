#include <iostream>
#include <fstream>
#include <iomanip>
#include "model.h"
#include "pid.h"

int main() {
    const double dt = 1.0;
    const int steps = 1500;

    HeaterModel plant(2.0, 150.0, 20.0, dt);
    PIDController pid(8.0, 80.0, 15.0, dt, 0.0, 100.0);

    std::ofstream csv("result_pids.csv");
    csv << "time,setpoint,temperature,u\n";

    double setpoint = 50.0;

    std::cout << "t\tSP\tT\tU(%)\n";

    for (int k = 0; k < steps; ++k) {
        double t = k * dt;

        if (t >= 800.0) setpoint = 70.0;

        double u = pid.calculate(setpoint, plant.getTemperature());
        double y = plant.step(u);

        if (k % 10 == 0) {
            std::cout << t << "\t" << setpoint << "\t" << std::fixed << std::setprecision(2)
                      << y << "\t" << u << "\n";
            csv << t << "," << setpoint << "," << y << "," << u << "\n";
        }
    }

    std::cout << "\nГотово! Файл result_pids.csv создан – открывай в Excel/Google Sheets и строй графики.\n";
    return 0;
}