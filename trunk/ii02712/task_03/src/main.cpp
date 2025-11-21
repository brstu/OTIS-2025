#include <iostream>
#include <vector>
#include "functions.h"

int main() {
    const int steps = 31;
    const double w = 100;

    std::vector<double> result = simulatePIDRegulatorUsingNonLinearModel(w, steps);

    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
    }

    return 0;
}