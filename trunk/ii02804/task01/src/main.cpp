#include <iostream>
#include <cmath>

using namespace std;

void simulateLinearModel(int n, double a, double b, double u0, double y0) {
    double y = y0;

    cout << "\n--- Linear Model ---\n";
    for (int tau = 0; tau < n; ++tau) {
        cout << "Time " << tau + 1 << ": " << y << endl;
        y = a * y + b * u0;
    }
}

void simulateNonlinearModel(int n, double a, double b, double c, double d, double u0, double y0) {
    double y = y0;
    double y_prev = y0;
    double u_prev = u0;  

    cout << "\n--- Nonlinear Model ---\n";
    for (int tau = 0; tau < n; ++tau) {
        cout << "Time " << tau + 1 << ": " << y << endl;

        double u;
        cout << "Enter heat input at time " << tau + 1 << ": ";
        cin >> u;

        double y_next = a * y - b * pow(y_prev, 2) + c * u + d * sin(u_prev);

        y_prev = y;
        y = y_next;
        u_prev = u;  
    }
}

int main() {
    int n;
    double u0;
    double y0;

    cout << "Enter number of time steps n: ";
    cin >> n;

    cout << "Enter initial heat input u0: ";
    cin >> u0;

    cout << "Enter initial temperature y0: ";
    cin >> y0;

    double a = 0.9;
    double b = 0.1;
    double c = 0.05;
    double d = 0.02;

    simulateLinearModel(n, a, b, u0, y0);
    simulateNonlinearModel(n, a, b, c, d, u0, y0);

    return 0;
}
