#include <iostream>
#include <vector>
#include "model.h"
#include "pid.h"

using namespace std;

int main() {
    double y0; 
    double a; 
    double b;
    double c;
    double d;
    int steps;
    double w;

    cout << "Initial y: ";
    cin >> y0;

    cout << "Linear a,b: ";
    cin >> a >> b;

    cout << "Nonlinear c,d: ";
    cin >> c >> d;

    cout << "Target w: ";
    cin >> w;

    cout << "Steps: ";
    cin >> steps;

    PID pid(0.4, 3.0, 0.1, 1.0);

    std::vector<double> u(steps);

    double y = y0;
    for (int i = 0; i < steps; i++) {
        double e = w - y;
        u[i] = pid.compute(e);
        y = y + 0.1 * (u[i]); // small plant
    }

    auto linY  = simulateLinear(steps, y0, a, b, u);
    auto nonY  = simulateNonlinear(steps, y0, a, b, c, d, u);

    cout << "\n--- Results ---\n";
    for (int i = 0; i < steps; i++) {
        cout << "Step " << i
             << " | u=" << u[i]
             << " | y_lin=" << linY[i]
             << " | y_non=" << nonY[i]
             << endl;
    }
}
