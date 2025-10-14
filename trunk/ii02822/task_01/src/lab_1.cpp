#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double u_current;
    double u_prev;
    double y;
    double a;
    double b;
    double c;
    double d;
    int count_steps;

    cout << "Enter initial temperature y: ";
    if (!(cin >> y)) {
        cerr << "Error: Invalid input for y" << endl;
        return 1;
    }

    cout << "Enter initial heat u: ";
    if (!(cin >> u_current)) {
        cerr << "Error: Invalid input for u" << endl;
        return 1;
    }

    u_prev = u_current;

    cout << "Enter constants a, b, c, d: ";
    if (!(cin >> a >> b >> c >> d)) {
        cerr << "Error: Invalid input for constants" << endl;
        return 1;
    }

    cout << "Enter number of steps: ";
    if (!(cin >> count_steps) || count_steps <= 0) {
        cerr << "Error: Invalid number of steps" << endl;
        return 1;
    }

    double y_linear = y;
    double y_nonlinear_prev = y;
    double y_nonlinear = y;

    cout << "\nInitial conditions:" << endl;
    cout << "y0 = " << y << ", u0 = " << u_current << endl;
    cout << "Constants: a=" << a << ", b=" << b << ", c=" << c << ", d=" << d << endl << endl;

    for (int i = 0; i < count_steps; i++)
    {
        if (i > 0) {
            u_prev = u_current;
        }

        double y_linear_next = a * y_linear + b * u_current;
        double y_nonlinear_next = a * y_nonlinear - b * y_nonlinear_prev * y_nonlinear_prev
            + c * u_current + d * sin(u_prev);

        cout << "Step " << i + 1 << ":" << endl;
        cout << "  Linear model: y_" << i + 1 << " = " << y_linear_next << endl;
        cout << "  Nonlinear model: y_" << i + 1 << " = " << y_nonlinear_next << endl;

        y_linear = y_linear_next;
        y_nonlinear_prev = y_nonlinear;
        y_nonlinear = y_nonlinear_next;
    }

    return 0;
}