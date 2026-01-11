#include <iostream>
#include "pid.h"

using namespace std;

int main()
{
    PID pid;

    double Kp = 1.2;
    double Ki = 0.3;
    double Kd = 0.1;

    double q0 = Kp + Ki + Kd;
    double q1 = -Kp - 2.0 * Kd;
    double q2 = Kd;

    initPID(pid, q0, q1, q2);

    double w = 271;  // заданное значение
    double y = 14;  // текущее значение объекта

    for (int k = 0; k < 200; k++)
    {
        double e = w - y;
        double u = updatePID(pid, e);

        cout << "Step " << k
            << " e = " << e
            << " u = " << u
            << endl;

        y = y + 0.1 * u;

        cout << "y = " << y << endl;
    }

    return 0;
}