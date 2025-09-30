#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

class TemperatureModel {
private:
    double a, b, c, d;
    double Y0;
    double C, R;
    double y_prev;
    double y_curr;
    double u_prev;

public:
    TemperatureModel(double a_val, double b_val, double c_val, double d_val,
                    double Y0_val, double C_val, double R_val, double y0)
        : a(a_val), b(b_val), c(c_val), d(d_val),
          Y0(Y0_val), C(C_val), R(R_val),
          y_prev(y0), y_curr(y0), u_prev(0.0) {}

    double linearModel(double u_tau) {
        double y_next = a * y_curr + b * u_tau;
        y_prev = y_curr;
        y_curr = y_next;
        return y_next;
    }

    double nonlinearModel(double u_tau) {
        double y_next = a * y_curr - b * y_prev * y_prev + c * u_tau + d * sin(u_prev);
        y_prev = y_curr;
        y_curr = y_next;
        u_prev = u_tau;
        return y_next;
    }

    double differentialEquation(double u_tau, double dt) {
        double dy_dt = u_tau / C + (Y0 - y_curr) / (R * C);
        y_curr += dy_dt * dt;
        return y_curr;
    }

    double getCurrentTemperature() const {
        return y_curr;
    }

    void reset(double y0) {
        y_prev = y0;
        y_curr = y0;
        u_prev = 0.0;
    }
};

void simulateLinearModel() {
    std::cout << "=== Linear Model Simulation ===" << std::endl;
    
    TemperatureModel model(0.8, 0.2, 0.1, 0.05, 20.0, 10.0, 5.0, 25.0);
    
    std::vector<double> u_input = {1.0, 1.5, 2.0, 1.8, 1.2, 0.8, 0.5, 0.3, 0.2, 0.1};
    
    std::cout << "Time\tInput\tTemperature" << std::endl;
    std::cout << "----------------------------" << std::endl;
    
    for (size_t t = 0; t < u_input.size(); ++t) {
        double temperature = model.linearModel(u_input[t]);
        std::cout << t + 1 << "\t" << u_input[t] << "\t" << std::fixed << std::setprecision(2) << temperature << std::endl;
    }
}

void simulateNonlinearModel() {
    std::cout << "\n=== Nonlinear Model Simulation ===" << std::endl;
    
    TemperatureModel model(0.7, 0.01, 0.3, 0.1, 20.0, 10.0, 5.0, 25.0);
    
    std::vector<double> u_input = {1.0, 1.2, 1.5, 1.3, 1.1, 0.9, 0.7, 0.5, 0.3, 0.2};
    
    std::cout << "Time\tInput\tTemperature" << std::endl;
    std::cout << "----------------------------" << std::endl;
    
    for (size_t t = 0; t < u_input.size(); ++t) {
        double temperature = model.nonlinearModel(u_input[t]);
        std::cout << t + 1 << "\t" << u_input[t] << "\t" << std::fixed << std::setprecision(2) << temperature << std::endl;
    }
}

void simulateDifferentialModel() {
    std::cout << "\n=== Differential Equation Model ===" << std::endl;
    
    TemperatureModel model(0.0, 0.0, 0.0, 0.0, 20.0, 10.0, 5.0, 25.0);
    
    std::vector<double> u_input = {2.0, 2.5, 3.0, 2.8, 2.2, 1.8, 1.5, 1.2, 1.0, 0.8};
    double dt = 0.1;
    
    std::cout << "Time\tInput\tTemperature" << std::endl;
    std::cout << "----------------------------" << std::endl;
    
    for (size_t t = 0; t < u_input.size(); ++t) {
        double temperature = model.differentialEquation(u_input[t], dt);
        std::cout << t + 1 << "\t" << u_input[t] << "\t" << std::fixed << std::setprecision(2) << temperature << std::endl;
    }
}

int main() {
    simulateLinearModel();
    simulateNonlinearModel();
    simulateDifferentialModel();
    
    return 0;
}