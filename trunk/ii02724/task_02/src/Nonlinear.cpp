#include <iostream>
#include <math.h>
#include "Nonlinear.h"
using namespace std;

void Nonlinear(Constant &c, int steps_count, double& current_temp, double current_heat, double next_temp, double previous_temp, double previous_heat) {


    for (int step = 1; step <= 1; step++)
    {

        next_temp = c.param_a * current_temp -
            c.param_b * previous_temp * previous_temp +
            c.param_c * current_heat +
            c.param_d * sin(previous_heat);


        previous_temp = current_temp;
        current_temp = next_temp;


        previous_heat = current_heat;

        if (step < steps_count) {
            cout << "Provide heat input for step " << step + 1 << ": ";
            cin >> current_heat;
        }
    }
}