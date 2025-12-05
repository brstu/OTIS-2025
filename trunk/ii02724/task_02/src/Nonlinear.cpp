#include <iostream>
#include <math.h>
#include "Nonlinear.h"
using namespace std;

void Nonlinear(double param_a, double param_b, int steps_count, double& current_temp, double current_heat, double next_temp, double previous_temp, double param_c, double param_d, double previous_heat) {
    //cout << "\n--- NON-LINEAR TEMPERATURE MODEL ---" << endl;
   // cout << "Formula: T_next = a*T - b*T_prev² + c*U + d*sin(U_prev)" << endl;

    for (int step = 1; step <= steps_count; step++)
    {

        next_temp = param_a * current_temp -
            param_b * previous_temp * previous_temp +
            param_c * current_heat +
            param_d * sin(previous_heat);


        previous_temp = current_temp;
        current_temp = next_temp;

        //cout << "Step " << step << " - Temperature: " << current_temp << endl;

        previous_heat = current_heat;

        if (step < steps_count) {
            cout << "Provide heat input for step " << step + 1 << ": ";
            cin >> current_heat;
        }
    }
}