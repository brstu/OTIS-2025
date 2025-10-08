#include <iostream>
#include <cmath>

using namespace std;

double linearModel(double y_tau, double u_tau, double a, double b) {
    return a * y_tau + b * u_tau;
}

double nonlinearModel(double y_tau, double y_tau_minus_1, double u_tau, double u_tau_minus_1, double a, double b, double c, double d) {
    return a * y_tau - b * y_tau_minus_1 * y_tau_minus_1 + c * u_tau + d * sin(u_tau_minus_1);
}

int main() {
    double a, b, c, d;
    double y0, u0;
    int n;

    cout << "Enter constants a, b, c, d: ";
    cin >> a >> b >> c >> d;
    cout << "Enter initial temperature y(0): ";
    cin >> y0;
    cout << "Enter initial input warmth u(0): ";
    cin >> u0;
    cout << "Enter number of steps: ";
    cin >> n;

    double y_current_linear = y0;
    double y_current_nonlinear = y0;
    double y_previous_nonlinear = y0;

    double u_current = u0;
    double u_previous = u0;

    cout << "Step\tLinear Model\tNonlinear Model\n";

    for (int tau = 0; tau < n; tau++) {

        double linear_result = linearModel(y_current_linear, u_current, a, b);
        double nonlinear_result = nonlinearModel(y_current_nonlinear, y_previous_nonlinear, u_current, u_previous, a, b, c, d);

        cout << tau + 1 << "\t" << linear_result << "\t\t" << nonlinear_result << "\n";

        y_current_linear = linear_result;

        y_previous_nonlinear = y_current_nonlinear;
        y_current_nonlinear = nonlinear_result;

    }

    return 0;
}
