#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    const int n = 12;
    const double y0 = 25.0;
    const double a = 0.93;
    const double b = 0.15;
    const double c = 0.10;
    const double d = 0.35;

    vector<double> u(n);
    for (int t = 0; t < n; ++t) {
        u[t] = 1.0 + 0.3 * sin(0.7 * (t + 1)) + 0.1 * cos(0.2 * (t + 1));
    }

    cout << "--- LINEAR MODEL ---\n";
    cout << "y(t+1) = a*y(t) + b*u(t)\n";

    double y = y0;
    for (int t = 0; t < n; ++t) {
        double yNext = a * y + b * u[t];
        cout << "Step " << (t + 1) << " | u=" << u[t] << " | y=" << yNext << "\n";
        y = yNext;
    }

    cout << "\n--- NONLINEAR MODEL ---\n";
    cout << "y(t+1) = a*y(t) - b*y(t-1)^2 + c*u(t) + d*sin(u(t-1))\n";

    double yCur = y0;
    double yPrev = 0.0;
    double uPrev = u[0];

    for (int t = 0; t < n; ++t) {
        double yNext = a * yCur
                     - b * (yPrev * yPrev)
                     + c * u[t]
                     + d * sin(uPrev);

        cout << "Step " << (t + 1) << " | u=" << u[t] << " | y=" << yNext << "\n";

        yPrev = yCur;
        yCur = yNext;
        uPrev = u[t];
    }

    return 0;
}
