#include <iostream>
#include <cmath>
using namespace std;

double a = 0.5;  
double b = 0.01;   
double c = 0.2;  
double d = 0.4;  

double linearModel(double y, double u) {
    return a * y + b * u;
}

double nonlinearModel(double y, double u, double y_pred, double u_pred) {
    return a * y - b * pow(y_pred, 2) + c * u + d * sin(u_pred);
}
  
int main() {
    double y;
    cout << "enter the initial temperature : ";
    cin >> y;
    double y_next = y;
    double y_pred;
    double u = 8;
    double u_pred;
    u_pred = u;
    int steps = 10;

    cout << "the linear model" << endl;
    cout << "Time:\tTemperature:" << endl;
    for (int i = 0; i < steps; i++) {
        y_pred = y_next;
        y_next = linearModel(y_next, u);
        cout << i + 1 << "\t" << y_next << endl;
    }
    cout << endl;
    y_next = y;
    cout << "non linear model:" << endl;
    cout << "Time:\tTemperature:" << endl;
    for (int i = 0; i < steps; i++) {
        y_next = nonlinearModel(y_next, u, y_pred, u_pred);
        cout << i + 1 << "\t" << y_next << endl; 
        y_pred = y_next;
        u_pred = u;
    }
    return 0;
}