#include <iostream>
#include <math.h>

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

    cout << "\n--- LINEAR TEMPERATURE MODEL ---" << endl;
    cout << "Formula: T_next = a * T_current + b * U_current" << endl;


    for (int step = 1; step <= steps_count; step++)
    {
        current_temp = param_a * current_temp + param_b * current_heat;
        cout << "Step " << step << " - Temperature: " << current_temp << endl;
    }


    current_temp = initial_temp;
    previous_temp = 0.0;
    previous_heat = current_heat;

    cout << "\n--- NON-LINEAR TEMPERATURE MODEL ---" << endl;
    cout << "Formula: T_next = a*T - b*T_prev² + c*U + d*sin(U_prev)" << endl;

    for (int step = 1; step <= steps_count; step++)
    {

        next_temp = param_a * current_temp -
                   param_b * previous_temp * previous_temp +
                   param_c * current_heat +
                   param_d * sin(previous_heat);


        previous_temp = current_temp;
        current_temp = next_temp;

        cout << "Step " << step << " - Temperature: " << current_temp << endl;

        previous_heat = current_heat;

        if (step < steps_count) {
            cout << "Provide heat input for step " << step + 1 << ": ";
            cin >> current_heat;
        }
    }

    cout << "\nSimulation completed!" << endl;
    return 0;
}