#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int model_type;
    cout << "Enter model type (1 for linear, 2 for nonlinear): ";
    cin >> model_type;

    if (model_type == 1) {
        double a, b;
        cout << "Enter parameters a and b: ";
        cin >> a >> b;

        double y0;
        cout << "Enter initial temperature y0: ";
        cin >> y0;

        int n;
        cout << "Enter number of steps n: ";
        cin >> n;

        vector<double> u(n);
        cout << "Enter input sequence u[0] to u[" << n - 1 << "]: ";
        for (int i = 0; i < n; i++) {
            cin >> u[i];
        }

        vector<double> y(n + 1);
        y[0] = y0;
        for (int tau = 0; tau < n; tau++) {
            y[tau + 1] = a * y[tau] + b * u[tau];
        }

        cout << "Computed temperatures y[0] to y[" << n << "]:" << endl;
        for (int i = 0; i <= n; i++) {
            cout << "y[" << i << "] = " << y[i] << endl;
        }

    }
    else if (model_type == 2) {
        double a, b, c, d;
        cout << "Enter parameters a, b, c, d: ";
        cin >> a >> b >> c >> d;

        double y0, y1;
        cout << "Enter initial temperatures y0 and y1: ";
        cin >> y0 >> y1;

        int n;
        cout << "Enter number of steps n: ";
        cin >> n;

        vector<double> u(n);
        cout << "Enter input sequence u[0] to u[" << n - 1 << "]: ";
        for (int i = 0; i < n; i++) {
            cin >> u[i];
        }

        vector<double> y(n + 1);
        y[0] = y0;
        y[1] = y1;
        for (int tau = 1; tau < n; tau++) {
            y[tau + 1] = a * y[tau] - b * pow(y[tau - 1], 2) + c * u[tau] + d * sin(u[tau - 1]);
        }

        cout << "Computed temperatures y[0] to y[" << n << "]:" << endl;
        for (int i = 0; i <= n; i++) {
            cout << "y[" << i << "] = " << y[i] << endl;
        }

    }
    else {
        cout << "Invalid model type selected." << endl;
        return 1;
    }

    return 0;
}