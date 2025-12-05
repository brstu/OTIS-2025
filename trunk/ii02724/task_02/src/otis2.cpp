#include <iostream>
#include <math.h>
#include "Linear.h"
#include "Nonlinear.h"
using namespace std;

int main()
{

    double current_temp;
    double previous_temp;
    double next_temp;
    double current_heat;
    double previous_heat;
    double param_a;
    double param_b;
    double param_c;
    double param_d;
    int steps_count;


    cout << "Input initial temperature and heat (separated by space): ";
    cin >> current_temp >> current_heat;

    cout << "Input coefficients a, b, c, d: ";
    cin >> param_a >> param_b >> param_c >> param_d;

    cout << "Input simulation steps count: ";
    cin >> steps_count;


    double initial_temp = current_temp;

    Linear(param_a, param_b, steps_count, current_temp, current_heat);

    current_temp = initial_temp;
    previous_temp = 0.0;
    previous_heat = current_heat;

    Nonlinear(param_a, param_b, steps_count, current_temp, current_heat, next_temp, previous_temp, param_c, param_d, previous_heat);
    cout << "\nSimulation completed!" << endl;
    return 0;
}