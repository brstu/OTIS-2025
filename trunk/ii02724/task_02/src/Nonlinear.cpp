#include <iostream>
#include <math.h>
#include "Nonlinear.h"
using namespace std;

void Nonlinear(double param_a, double param_b, double& current_temp, double current_heat, double next_temp, double previous_temp, double param_c, double param_d, double previous_heat) {


    for (int step = 1; step <= 1; step++)
    {

        next_temp = param_a * current_temp -
            param_b * previous_temp * previous_temp +
            param_c * current_heat +
            param_d * sin(previous_heat);


        previous_temp = current_temp;
        current_temp = next_temp;


        previous_heat = current_heat;

        if (step < steps_count) {
            cout << "Provide heat input for step " << step + 1 << ": ";
            cin >> current_heat;
        }
    }
}