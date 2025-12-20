#include "functions.h"
#include <cmath>
#include <fstream>

double linearPlant(double y, double u)
{
    return A * y + B * u;
}

double nonlinearPlant(double y, double u, double y_prev, double u_prev)
{
    return A * y
         - B * y_prev * y_prev
         + C * u
         + D * std::sin(u_prev);
}

std::vector<double> runSimulation(double setpoint, int steps)
{
    double y = 1.0;
    double u = 0.0;

    double y_prev = y;
    double u_prev = u;

    double e  = setpoint - y;
    double e1 = e;
    double e2 = e;

    std::vector<double> history;
    history.reserve(steps);

    for (int k = 0; k < steps; ++k)
    {
        double du = Q0 * e + Q1 * e1 + Q2 * e2;
        u += du;

        double y_new = nonlinearPlant(y, u, y_prev, u_prev);
        double e_new = setpoint - y_new;

        history.push_back(y_new);

        y_prev = y;
        u_prev = u;
        y = y_new;

        e2 = e1;
        e1 = e;
        e  = e_new;
    }

    return history;
}

void saveToCSV(const std::string& filename,
               const std::vector<double>& data)
{
    std::ofstream file(filename);
    file << "k,y\n";

    for (size_t i = 0; i < data.size(); ++i)
    {
        file << i << "," << data[i] << "\n";
    }
}
