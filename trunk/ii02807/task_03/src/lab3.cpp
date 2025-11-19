#include <iostream>
#include "pid.h"
#include "model.h"

using namespace std;

/**
 * @brief Main program for PID controller simulation.
 *
 * The program asks the user to enter:
 * - Initial system state y0
 * - Model parameters a and b
 * - Target value w
 * - Number of simulation steps
 *
 * Then it simulates the system controlled by a PID regulator.
 */
int main() {
    double y0, a, b;
    cout << "Enter the initial value of y: ";
    cin >> y0;

    cout << "Enter the model parameters a and b (e.g. 0.9 0.1): ";
    cin >> a >> b;

    double w;
    cout << "Enter the target value w: ";
    cin >> w;

    int steps;
    cout << "Enter the number of simulation steps: ";
    cin >> steps;

    /// PID controller parameters
    double K  = 0.4;
    double T  = 3.0;
    double Td = 0.1;
    double T0 = 1.0;

    PID pid(K, T, Td, T0);
    double y = y0;

    for (int k = 0; k < steps; k++) {
        double e = w - y;          ///< Error signal
        double u = pid.compute(e); ///< Control signal
        y = linear(y, u, a, b);    ///< System update

        cout << "Step " << k
             << "  e=" << e
             << "  u=" << u
             << "  y=" << y << endl;
    }

    return 0;
}
