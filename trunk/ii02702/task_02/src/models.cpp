#include "models.hpp"
#include <cmath>

std::vector<double> simulateLinearModel(double y, double u, int t, double a, double b) {
    std::vector<double> results;
    for (int i = 0; i <= t; i++) {
        results.push_back(y);
        y = a * y + b * u;
    }
    return results;
}

std::vector<double> simulateNonLinearModel(double y, double u, int t, double a, double b, double c, double d) {
    std::vector<double> results;

    // Инициализируем предыдущие выходные и входные значения с помощью смещений.
    // Смещения (yOffset и uOffset) представляют собой разницу между начальным и предыдущим состояниями,
    // позволяя нелинейной модели начать с заданной истории для y и u.
    const double y_offset = 0.1;
    const double u_offset = 0.1;

    const double u_step = 0.5;       // шаг изменения для переменной u в нелинейной модели

    double prevY = y - y_offset;
    double prevU = u - u_offset;

    for (int i = 0; i <= t; i++) {
        results.push_back(y);
        double nextY = a * y - b * prevY * prevY + c * u + d * sin(prevU);
        prevU += u_step;
        prevY = y;
        y = nextY;
    }
    return results;
}