#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "pid_controller.h"
#include "model.h"

double nonlinearModelUpdate(double u, double dt) {
    static double y_prev_nl = 0.0;
    const double K_nl = 1.0;
    const double T_nl = 0.5;
    const double a = 1.0 - dt / T_nl;
    const double b = K_nl * dt / T_nl;
    double y = a * y_prev_nl + b * u;

    if (y > 25.0) {
        y = 25.0;
    }
    if (y < -25.0) {
        y = -25.0;
    }

    y_prev_nl = y;
    return y;
}

std::vector<double> simulateSystem(PIDController& pid,
    const std::vector<double>& setpoints,
    bool use_nonlinear = false,
    double dt = 0.1) {

    std::vector<double> results;
    results.reserve(setpoints.size());

    if (!use_nonlinear) {
        modelInit(1.0, 0.5);
    }

    double current_value = 0.0;

    for (const double& setpoint : setpoints) {
        const double control_signal = pid.calculate(setpoint, current_value);
        double new_value;

        if (use_nonlinear) {
            new_value = nonlinearModelUpdate(control_signal, dt);
        }
        else {
            new_value = modelUpdate(control_signal, dt);
        }

        results.push_back(new_value);
        current_value = new_value;
    }

    return results;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "=== SIMULATION СИСТЕМЫ УПРАВЛЕНИЯ ===\n\n";

    const double K = 0.8;
    const double Ti = 4.0;
    const double Td = 0.05;
    const double T = 0.1;

    PIDController pid(K, Ti, Td, T);

    std::vector<double> setpoints;
    setpoints.reserve(35);

    for (int i = 0; i < 15; ++i) {
        setpoints.push_back(20.0);
    }
    for (int i = 0; i < 10; ++i) {
        setpoints.push_back(5.0);
    }
    for (int i = 0; i < 10; ++i) {
        setpoints.push_back(15.0);
    }

    std::cout << "1. LINEAR MODEL SIMULATION:\n";
    pid.reset();
    modelInit(1.0, 0.5);
    const auto linear_results = simulateSystem(pid, setpoints, false, T);

    std::cout << "\n2. NONLINEAR MODEL SIMULATION:\n";
    PIDController pid_nl(K, Ti, Td, T);
    pid_nl.reset();
    const auto nonlinear_results = simulateSystem(pid_nl, setpoints, true, T);

    std::cout << "\n3. COMPARISON RESULTS:\n";
    std::cout << std::string(75, '=') << "\n";
    std::cout << std::setw(6) << "Step"
        << std::setw(12) << "Setpoint"
        << std::setw(18) << "Linear Output"
        << std::setw(18) << "Nonlinear"
        << std::setw(15) << "Control" << "\n";
    std::cout << std::string(75, '-') << "\n";

    pid.reset();
    modelInit(1.0, 0.5);
    double current_value = 0.0;

    for (size_t i = 0; i < setpoints.size(); ++i) {
        const double control_signal = pid.calculate(setpoints[i], current_value);
        current_value = modelUpdate(control_signal, T);

        if (std::fabs(current_value - linear_results[i]) > 0.001) {
            std::cerr << "Warning: mismatch at step " << i
                << ": " << current_value << " vs " << linear_results[i] << std::endl;
        }

        std::cout << std::setw(6) << i
            << std::setw(12) << std::fixed << std::setprecision(2) << setpoints[i]
            << std::setw(18) << std::setprecision(4) << linear_results[i]
            << std::setw(18) << nonlinear_results[i]
            << std::setw(15) << std::setprecision(3) << control_signal << "\n";

        if (i % 10 == 9) {
            std::cout << std::string(75, '-') << "\n";
        }
    }

    std::cout << "\n4. PERFORMANCE ANALYSIS:\n";
    std::cout << std::string(50, '-') << "\n";

    if (const int steady_start = 20, steady_end = 25;
        steady_start < static_cast<int>(linear_results.size()) &&
        steady_end < static_cast<int>(linear_results.size())) {

        double lin_sum = 0.0;
        double nl_sum = 0.0;
        int count = 0;

        for (int i = steady_start; i <= steady_end; ++i) {
            lin_sum += linear_results[i];
            nl_sum += nonlinear_results[i];
            ++count;
        }

        const double lin_avg = lin_sum / count;
        const double nl_avg = nl_sum / count;

        std::cout << "Steady-state average (target = 20.0):\n";
        std::cout << "  Linear model:    " << std::setprecision(3) << lin_avg << "\n";
        std::cout << "  Nonlinear model: " << nl_avg << "\n";
        std::cout << "  Difference:      " << (nl_avg - lin_avg)
            << " (" << std::setprecision(1)
            << std::fabs(100.0 * (nl_avg - lin_avg) / lin_avg) << "%)\n";
    }

    double lin_max = 0.0;
    double nl_max = 0.0;

    for (const double& value : linear_results) {
        if (value > lin_max) {
            lin_max = value;
        }
    }

    for (const double& value : nonlinear_results) {
        if (value > nl_max) {
            nl_max = value;
        }
    }

    std::cout << "\nMaximum overshoot:\n";
    std::cout << "  Linear model:    " << std::setprecision(3) << lin_max << "\n";
    std::cout << "  Nonlinear model: " << nl_max << "\n";

    std::cout << "\n5. SYSTEM PARAMETERS:\n";
    std::cout << std::string(30, '-') << "\n";

    double pK = 0.0;
    double pTi = 0.0;
    double pTd = 0.0;
    double pT = 0.0;

    pid.getParameters(pK, pTi, pTd, pT);

    std::cout << "PID Controller:\n";
    std::cout << "  K = " << pK << ", Ti = " << pTi
        << ", Td = " << pTd << ", T = " << pT << "\n";

    std::cout << "\nSimulation parameters:\n";
    std::cout << "  Total steps: " << setpoints.size() << "\n";
    std::cout << "  Time step (dt): " << T << " sec\n";
    std::cout << "  Model: K_obj = 1.0, T_obj = 0.5\n";

    std::cout << "\n" << std::string(75, '=') << "\n";
    std::cout << "SIMULATION COMPLETED SUCCESSFULLY!\n";

    return 0;
}