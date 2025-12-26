#include <iostream>
#include <vector>
#include "functions.h"

int main() {
    const int steps = 300;
    const double setpoint = 4.0;

    std::vector<double> y_values = runSimulation(setpoint, steps);

    for (size_t i = 0; i < y_values.size(); ++i) {
        std::cout << i << " : " << y_values[i] << std::endl;
    }

    saveToCSV("pid_w4.csv", y_values);

    return 0;
}
