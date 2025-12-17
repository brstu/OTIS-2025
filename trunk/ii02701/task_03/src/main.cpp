#include <iostream>
#include "pid.h"

using namespace std;

int main() {
    PID pid;

    initPID(pid, 0.6, 0.3, 0.1);

    double w = 1.0;  // заданное значение
    double y = 0.0;  // текущее значение объекта

    for (int k = 0; k < 20; k++) {
        double e = w - y;
        double u = updatePID(pid, e);

        cout << "Шаг " << k
            << " e=" << e
            << " u=" << u
            << endl;

        // Простейшая модель объекта управления
        y = y + 0.1 * u;
    }

    return 0;
}