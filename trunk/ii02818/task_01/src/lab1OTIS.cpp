#include <iostream>
#include <vector>
#include <cmath>

class TemperatureModel {
private:
    double a;
    double b;
    double c;
    double d;
    double y_prev;  
    double y_curr;
    double u_prev;
    double u_curr;

public:
    TemperatureModel(double a, double b, double c, double d)
        : a(a), b(b), c(c), d(d),  
        y_prev(0), y_curr(0),   
        u_prev(0), u_curr(0) {
    }  

    void setInitialState(double y0, double y1, double u0, double u1) {
        y_prev = y0;
        y_curr = y1;
        u_prev = u0;
        u_curr = u1;
    }

    void updateControl(double u_new) {
        u_prev = u_curr;
        u_curr = u_new;
    }

    std::vector<double> simulateLinear(int time_steps) const {
        std::vector<double> temperatures(time_steps);

        if (time_steps >= 1) temperatures[0] = y_prev;
        if (time_steps >= 2) temperatures[1] = y_curr;

        for (int t = 2; t < time_steps; t++) {
            temperatures[t] = a * temperatures[t - 1] + b * u_curr;
        }

        return temperatures;
    }

    std::vector<double> simulateNonlinear(int time_steps) const {
        std::vector<double> temperatures(time_steps);

        if (time_steps >= 1) temperatures[0] = y_prev;
        if (time_steps >= 2) temperatures[1] = y_curr;

        for (int t = 2; t < time_steps; t++) {
            temperatures[t] = a * temperatures[t - 1]
                - b * std::pow(temperatures[t - 2], 2)
                + c * u_curr
                + d * std::sin(u_prev);
        }

        return temperatures;
    }
};

int main() {
    double a = 0.2;
    double b = 0.3;
    double c = 0.4;
    double d = 0.5;
    TemperatureModel model(a, b, c, d);
    model.setInitialState(20.0, 21.0, 1.0, 1.5);

    int simulation_time;
    std::cout << "Enter simulation time steps: ";
    std::cin >> simulation_time;

    std::cout << "Model parameters: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;

    std::cout << "\nLinear Model Simulation:" << std::endl;
    auto linear_results = model.simulateLinear(simulation_time);
    for (int t = 0; t < linear_results.size(); t++) {
        std::cout << "Time t=" << t << ": y(t) = " << linear_results[t] << std::endl;
    }

    std::cout << "\nNonlinear Model Simulation:" << std::endl;
    auto nonlinear_results = model.simulateNonlinear(simulation_time);
    for (int t = 0; t < nonlinear_results.size(); t++) {
        std::cout << "Time t=" << t << ": y(t) = " << nonlinear_results[t] << std::endl;
    }

    return 0;
}