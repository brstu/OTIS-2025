#include "model.h"

int main() {
    // параметры линейной модели
    double a1 = 0.1;
    double b1 = 0.3;
    double u1 = 0.5;
    int n1 = 10;
    simulateLinear(a1, b1, u1, n1);

    // параметры нелинейной модели
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    double u2 = 0.15;
    int n2 = 10;
    simulateNonlinear(p, u2, n2);

    return 0;
}