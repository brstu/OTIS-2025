#include "model.h"
#include <iostream>
#include <limits>
#include <string>

double linearModel(double y_current, double u_current, const ModelParameters& params) {
    return params.a * y_current + params.b * u_current;
}

double nonlinearModel(double y_current, double y_previous, double u_current, double u_previous, const ModelParameters& params) {
    return params.a * y_current - params.b * y_previous * y_previous + params.c * u_current + params.d * sin(u_previous);
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void readDouble(const std::string& text, double& value) {
    while (true) {
        std::cout << text;
        if (std::cin >> value) {
            return;
        }
        else {
            std::cout << "Invalid input. Please enter a numeric value.\n";
            clearInput();
        }
    }
}

void readPositiveInt(const std::string& text, int& value) {
    while (true) {
        std::cout << text;
        if (std::cin >> value && value > 0) {
            return;
        }
        else {
            std::cout << "Invalid input. Please enter a positive integer.\n";
            clearInput();
        }
    }
}