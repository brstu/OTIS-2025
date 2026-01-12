#include <iostream>
#include <vector>
#include "functions.h"

int main() {
    const int steps = 300;
    const double w = 4.0;

    std::vector<double> result = simulatePIDRegulatorUsingNonLinearModel(w, steps);

    for (int i = 0; i < result.size(); i++) {
        std::cout << i << ':' << result[i] << std::endl;
    }

    return 0;
}