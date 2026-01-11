#include <iostream>
#include <cmath>

using namespace std;

struct ModelParams {
    double a;
    double b;
    double c;
    double d;
};

double linearModel(double y_tau, double u_tau, const ModelParams& params) {
    return params.a * y_tau + params.b * u_tau;
}

double nonlinearModel(double y_tau, double y_tau_minus_1, double u_tau, double u_tau_minus_1, const ModelParams& params) {
    return params.a * y_tau
        - params.b * y_tau_minus_1 * y_tau_minus_1
        + params.c * u_tau
        + params.d * sin(u_tau_minus_1);
}

int main() {
    ModelParams params;

    double y0;
    double u0;
    int n;

    cout << "Enter constants a, b, c, d: ";
    cin >> params.a >> params.b >> params.c >> params.d;

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
        double linear_result = linearModel(y_current_linear, u_current, params);
        double nonlinear_result = nonlinearModel(y_current_nonlinear, y_previous_nonlinear, u_current, u_previous, params);

        cout << tau + 1 << "\t" << linear_result << "\t\t" << nonlinear_result << "\n";

        y_current_linear = linear_result;

        y_previous_nonlinear = y_current_nonlinear;
        y_current_nonlinear = nonlinear_result;

    }

    return 0;
}
