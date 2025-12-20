/**
 * @file simulation.cpp
 * @brief PID temperature control system simulation program
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>
#include "pid_controller.h"

/**
 * @brief Plant model (heater/cooler)
 * @param current_temp Current temperature
 * @param control_signal Control signal (0-100%)
 * @param dt Time step
 * @param room_temp Ambient temperature
 * @return New temperature
 */
double temperatureModel(double current_temp, double control_signal, double dt, double room_temp = 20.0) {
    // First-order model
    double tau = 10.0;  // System time constant
    double max_heating_power = 5.0;  // Maximum heating power in °C/s

    // Convert control signal (0-100%) to heating power
    double heating_power = max_heating_power * (control_signal / 100.0);

    // Calculate temperature change
    double dtemp = (heating_power - (current_temp - room_temp) / tau) * dt;

    return current_temp + dtemp;
}

/**
 * @brief Main program function
 * @return Program exit code
 */
int main() {
    // Create PID controller
    PIDController pid(2.5, 0.5, 1.0, 0, 100);

    // Set target temperature
    double setpoint = 75.0;  // Target temperature °C
    pid.setSetpoint(setpoint);

    // Initial conditions
    double current_temp = 20.0;  // Initial temperature °C
    double dt = 0.1;  // Time step in seconds
    int simulation_time = 100;  // Simulation time in seconds
    int steps = static_cast<int>(simulation_time / dt);

    // Data storage vectors
    std::vector<double> time_points;
    std::vector<double> temperatures;
    std::vector<double> control_signals;
    std::vector<double> setpoints;

    // Random number generator for noise
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> noise(0.0, 0.2);  // Noise with std dev 0.2°C

    std::cout << "Starting PID controller simulation..." << std::endl;
    std::cout << "Target temperature: " << setpoint << " °C" << std::endl;
    std::cout << "Simulation time: " << simulation_time << " sec" << std::endl;
    std::cout << "Time step: " << dt << " sec" << std::endl;

    // Main simulation loop
    for (int i = 0; i < steps; i++) {
        double time = i * dt;

        // Change setpoint during simulation
        if (time > 40 && time < 41) {
            setpoint = 50.0;  // Lower temperature
            pid.setSetpoint(setpoint);
        }
        else if (time > 70 && time < 71) {
            setpoint = 85.0;  // Raise temperature
            pid.setSetpoint(setpoint);
        }

        // Add noise to measured temperature
        double measured_temp = current_temp + noise(gen);

        // Calculate control signal
        double control = pid.calculate(measured_temp, dt);

        // Update temperature using model
        current_temp = temperatureModel(current_temp, control, dt);

        // Save data
        time_points.push_back(time);
        temperatures.push_back(measured_temp);
        control_signals.push_back(control);
        setpoints.push_back(pid.getSetpoint());

        // Display progress
        if (i % 100 == 0) {
            std::cout << "Time: " << time
                << " s, Temperature: " << measured_temp
                << " °C, Control: " << control << "%" << std::endl;
        }
    }

    // Write data to CSV file
    std::ofstream csv_file("temperature_data.csv");
    if (csv_file.is_open()) {
        csv_file << "Time,Temperature,Setpoint,Control_Signal\n";
        for (size_t i = 0; i < time_points.size(); i++) {
            csv_file << time_points[i] << ","
                << temperatures[i] << ","
                << setpoints[i] << ","
                << control_signals[i] << "\n";
        }
        csv_file.close();
        std::cout << "\nData saved to temperature_data.csv" << std::endl;
    }
    else {
        std::cerr << "Error creating CSV file!" << std::endl;
        return 1;
    }

    // Output statistics
    std::cout << "\n=== Simulation Statistics ===" << std::endl;
    std::cout << "Number of data points: " << time_points.size() << std::endl;
    std::cout << "Final temperature: " << temperatures.back() << " °C" << std::endl;
    std::cout << "Setpoint: " << setpoint << " °C" << std::endl;
    std::cout << "Control error: " << setpoint - temperatures.back() << " °C" << std::endl;

    return 0;
}