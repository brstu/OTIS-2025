#include "Simulater.h"

struct SystemConstants {
    const double a = 0.5f;
    const double b = 0.2f;
    const double c = 0.15f;
    const double d = 0.3f;
    const double u = 1.2f;
};

void printResult(int iteration, double value) { 
    std::cout << " t" << iteration + 1 << " = " << value << std::endl;
}


void simulateSystem(double initialY1, int iterations) {
    SystemConstants constants;

    LinearSystem linearSys(constants.a, constants.b, constants.u);
    NonlinearSystem nonlinearSys(constants.a, constants.b,
        constants.c, constants.d, constants.u);

    double y0 = initialY1;
    double y1 = initialY1;
    double y2;

    std::cout << "\nLinear system simulation:" << std::endl;
    for (int i = 0; i < iterations; i++) {
        y2 = linearSys.calculateNext(y1);
        printResult(i, y2);
        y1 = y2;
    }

    y0 = initialY1;
    y1 = initialY1;

    std::cout << "\nNonlinear system simulation:" << std::endl;
    for (int i = 0; i < iterations; i++) {
        y2 = nonlinearSys.calculateNext(y1, y0);
        printResult(i, y2);
        y0 = y1;
        y1 = y2;
    }
}
