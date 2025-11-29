#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <functional>  // Добавлен для std::function

class TemperatureModel {
private:
    // Model parameters
    double a{ 0.0 };
    double b{ 0.0 };
    double c{ 0.0 };
    double d{ 0.0 };
    double Y0{ 0.0 };
    double C{ 0.0 };
    double R{ 0.0 };

    // State variables
    double y_prev{ 0.0 };
    double y_curr{ 0.0 };
    double u_prev{ 0.0 };

public:
    // Constructor with parameter validation
    TemperatureModel(double a_val, double b_val, double c_val, double d_val,
        double Y0_val, double C_val, double R_val, double y0) {
        // Validate critical parameters
        if (C_val == 0.0) {
            throw std::invalid_argument("C (capacitance) cannot be zero");
        }
        if (R_val == 0.0) {
            throw std::invalid_argument("R (resistance) cannot be zero");
        }

        a = a_val;
        b = b_val;
        c = c_val;
        d = d_val;
        Y0 = Y0_val;
        C = C_val;
        R = R_val;
        y_prev = y0;
        y_curr = y0;
        // u_prev uses default initialization (0.0)
    }

    double linearModel(double u_tau) {
        double y_next = a * y_curr + b * u_tau;
        updateState(y_next, u_tau);
        return y_next;
    }

    double nonlinearModel(double u_tau) {
        double y_next = a * y_curr - b * y_prev * y_prev + c * u_tau + d * std::sin(u_prev);
        updateState(y_next, u_tau);
        return y_next;
    }

    double differentialEquation(double u_tau, double dt) {
        if (dt <= 0.0) {
            throw std::invalid_argument("Time step must be positive");
        }

        double dy_dt = u_tau / C + (Y0 - y_curr) / (R * C);
        double y_next = y_curr + dy_dt * dt;
        updateState(y_next, u_tau);
        return y_next;
    }

    double getCurrentTemperature() const {
        return y_curr;
    }

    void reset(double y0) {
        y_prev = y0;
        y_curr = y0;
        u_prev = 0.0;
    }

private:
    void updateState(double y_next, double u_current) {
        y_prev = y_curr;
        y_curr = y_next;
        u_prev = u_current;
    }
};

// Simulation functions with better output formatting
void simulateModel(const std::string& title,
    const std::vector<double>& u_input,
    std::function<double(TemperatureModel&, double)> modelFunc,
    TemperatureModel initialModel) {  // Изменено на передачу по значению

    std::cout << "\n" << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    TemperatureModel model = initialModel;

    std::cout << "Time\tInput\tTemperature" << std::endl;
    std::cout << "----\t-----\t-----------" << std::endl;

    for (size_t t = 0; t < u_input.size(); ++t) {
        double temperature = modelFunc(model, u_input[t]);
        std::cout << t + 1 << "\t" << u_input[t] << "\t"
            << std::fixed << std::setprecision(3) << temperature << std::endl;
    }
}

void simulateDifferentialModelWithTimeStep(const std::string& title,
    const std::vector<double>& u_input,
    double dt,
    TemperatureModel initialModel) {  // Изменено на передачу по значению

    std::cout << "\n" << title << " (dt=" << dt << ")" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    TemperatureModel model = initialModel;

    std::cout << "Time\tInput\tTemperature" << std::endl;
    std::cout << "----\t-----\t-----------" << std::endl;

    for (size_t t = 0; t < u_input.size(); ++t) {
        double temperature = model.differentialEquation(u_input[t], dt);
        std::cout << t + 1 << "\t" << u_input[t] << "\t"
            << std::fixed << std::setprecision(3) << temperature << std::endl;
    }
}

int main() {
    try {
        // Linear model simulation
        TemperatureModel linearModel(0.8, 0.2, 0.1, 0.05, 20.0, 10.0, 5.0, 25.0);
        std::vector<double> u_linear = { 1.0, 1.5, 2.0, 1.8, 1.2, 0.8, 0.5, 0.3, 0.2, 0.1 };

        simulateModel("Linear Model Simulation", u_linear,
            [](TemperatureModel& model, double u) { return model.linearModel(u); },
            linearModel);

        // Nonlinear model simulation  
        TemperatureModel nonlinearModel(0.7, 0.01, 0.3, 0.1, 20.0, 10.0, 5.0, 25.0);
        std::vector<double> u_nonlinear = { 1.0, 1.2, 1.5, 1.3, 1.1, 0.9, 0.7, 0.5, 0.3, 0.2 };

        simulateModel("Nonlinear Model Simulation", u_nonlinear,
            [](TemperatureModel& model, double u) { return model.nonlinearModel(u); },
            nonlinearModel);

        // Differential equation model simulation
        TemperatureModel diffModel(0.0, 0.0, 0.0, 0.0, 20.0, 10.0, 5.0, 25.0);
        std::vector<double> u_diff = { 2.0, 2.5, 3.0, 2.8, 2.2, 1.8, 1.5, 1.2, 1.0, 0.8 };

        simulateDifferentialModelWithTimeStep("Differential Equation Model",
            u_diff, 0.1, diffModel);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}