#include <iostream>
#include <cmath>
using namespace std;

double nextLinear(double a, double b, double u, double y) {
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps) {
    cout << "Линейная модель" << endl;
    double y = 0.0;
    for (int i = 0; i < steps; i++) {
        cout << "τ=" << i << ": y=" << y << endl;
        y = nextLinear(a, b, u, y);
    }
}

double nextNonlinear(double a, double b, double c, double d, 
                    double u, double u_prev, double y, double y_prev) {
    return a * y - b * (y_prev * y_prev) + c * u + d * sin(u_prev);
}

void simulateNonlinear(double a, double b, double c, double d, double u, int steps) {
    cout << "Нелинейная модель" << endl;
    double y = 0.0, y_prev = 0.0;
    double u_prev = 0.0;
    
    for (int i = 0; i < steps; i++) {
        cout << "τ=" << i << ": y=" << y << endl;
            double y_next = nextNonlinear(a, b, c, d, u, u_prev, y, y_prev);
            y_prev = y;
            y = y_next;
        
        u_prev = u; 
    }
}

int main() {
    double a1 = 0.3, b1 = 0.3, u1 = 0.9;
    int n1 = 10;
    simulateLinear(a1, b1, u1, n1);
    cout << endl;

    double a2 = 0.1, b2 = 0.2, c2 = 0.4, d2 = 0.2, u2 = 0.8;
    int n2 = 10;
    simulateNonlinear(a2, b2, c2, d2, u2, n2);

    return 0;
}