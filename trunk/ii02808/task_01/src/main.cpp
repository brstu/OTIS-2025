#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double params[4] = {0.8, 0.6, 0.4, 2.2};
double heat_input = 0.8;

vector<double> linearSim(int n, double start_temp) {
    vector<double> data(n);
    data[0] = start_temp;
    
    for (int i = 1; i < n; i++) {
        data[i] = params[0] * data[i-1] + params[1] * heat_input;
    }
    return data;
}

vector<double> nonlinearSim(int n, double start_temp) {
    vector<double> data(n);
    data[0] = start_temp;
    
    if (n > 1) {
        data[1] = params[0] * data[0] + params[2] * heat_input + params[3] * sin(heat_input);
    }
    
    for (int i = 2; i < n; i++) {
        data[i] = params[0] * data[i-1] - params[1] * data[i-2] * data[i-2] 
                 + params[2] * heat_input + params[3] * sin(heat_input);
    }
    return data;
}

int main() {
    double start_temp;
    int steps;
    
    cout << "Enter starting temperature: ";
    cin >> start_temp;
    
    cout << "Enter number of steps: ";
    cin >> steps;
    
    while (steps < 1) {
        cout << "Steps must be 1 or more: ";
        cin >> steps;
    }
    
    vector<double> linear_data = linearSim(steps, start_temp);
    vector<double> nonlinear_data = nonlinearSim(steps, start_temp);
    
    cout << "\nLinear Model Results:" << endl;
    for (int i = 0; i < steps; i++) {
        cout << "Step " << i << ": " << linear_data[i] << endl;
    }
    
    cout << "\nNonlinear Model Results:" << endl;
    for (int i = 0; i < steps; i++) {
        cout << "Step " << i << ": " << nonlinear_data[i] << endl;
    }
    
    return 0;
}
