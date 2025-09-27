#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n;
    double a, b, c, d, y0, u0;
    cin >> n >> a >> b >> c >> d >> y0 >> u0;
    vector<double> u(n + 1), y(n + 1);
    u[0] = u0;
    y[0] = y0;
    for (int t = 0; t < n; t++) {
        cin >> u[t + 1];
        y[t + 1] = a * y[t] - b * y[t] * y[t] + c * u[t] + d * sin(u[t]);
    }
    for (int t = 0; t <= n; t++) cout << t << " " << y[t] << "\n";
}