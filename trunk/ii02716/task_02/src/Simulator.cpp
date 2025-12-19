#include "Simulater.h"

struct SystemConstants {
    const float a = 0.5f;
    const float b = 0.2f;
    const float c = 0.15f;
    const float d = 0.3f;
    const float u = 1.2f;
};

void printResult(int iteration, float value) { 
    std::cout << " t" << iteration + 1 << " = " << value << std::endl;
}


void simulateSystem(float initialY1, int iterations) {
    SystemConstants constants;

    LinearSystem linearSys(constants.a, constants.b, constants.u);
    NonlinearSystem nonlinearSys(constants.a, constants.b,
        constants.c, constants.d, constants.u);

    float y0 = initialY1;
    float y1 = initialY1;
    float y2;

    std::cout << "\nLinear system simulation:" << std::endl;
    for (int i = 0; i < iterations; i++) {
        y2 = linearSys.calculateNext(y1);
        printResult(i, y2);
        y0 = y1;
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