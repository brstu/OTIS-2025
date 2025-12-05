#include <iostream>
#include <math.h>
#include "Linear.h"
#include "Nonlinear.h"
using namespace std;

int main()
{

    double current_temp = 0;
    double previous_temp = 0;
    double next_temp = 0;
    double current_heat = 0;
    double previous_heat = 0;
    double param_a = 0;
    double param_b = 0;
    double param_c = 0;
    double param_d = 0;
    int steps_count = 0;


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