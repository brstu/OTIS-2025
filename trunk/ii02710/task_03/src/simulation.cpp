/**
 * @file simulation.cpp
 * @brief PID temperature control system simulation program
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <limits>
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
 * @brief Get temperature input from user
 * @return Target temperature
 */
double getTemperatureInput() {
    double temperature;

    std::cout << "\n=== Temperature Input ===\n";

    while (true) {
        std::cout << "Enter target temperature (°C): ";
        std::cin >> temperature;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        }
        else if (temperature < -273.15) {
            std::cout << "Temperature cannot be below absolute zero (-273.15°C).\n";
        }
        else if (temperature > 1000) {
            std::cout << "Warning: Very high temperature (>1000°C). Continue? (y/n): ";
            char confirm;
            std::cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    return temperature;
}

/**
 * @brief Display main menu
 * @return User's choice
 */
int displayMenu() {
    int choice;
    while (true) {
        std::cout << "\n=== PID Controller Simulation ===\n";
        std::cout << "1. Run simulation with default temperature (75°C)\n";
        std::cout << "2. Run simulation with custom temperature\n";
        std::cout << "3. Exit\n";
        std::cout << "Select option (1-3): ";

        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

/**
 * @brief Run simulation with specified parameters
 * @param pid PID controller instance
 * @param setpoint Target temperature
 * @param initial_temp Initial temperature
 * @param dt Time step
 * @param simulation_time Total simulation time
 */
void runSimulation(PIDController& pid,
    double setpoint,
    double initial_temp,
    double dt,
    int simulation_time) {

    // Initial conditions
    double current_temp = initial_temp;
    int steps = static_cast<int>(simulation_time / dt);

    // Data storage vectors
    std::vector<double> time_points;
    std::vector<double> temperatures;
    std::vector<double> control_signals;
    std::vector<double> setpoints;

    // Set target temperature
    pid.setSetpoint(setpoint);

    std::cout << "\n=== Starting Simulation ===\n";
    std::cout << "Initial temperature: " << initial_temp << " °C\n";
    std::cout << "Target temperature: " << setpoint << " °C\n";
    std::cout << "Simulation time: " << simulation_time << " sec\n";
    std::cout << "Time step: " << dt << " sec\n";

    // Main simulation loop
    for (int i = 0; i < steps; i++) {
        double time = i * dt;

        // Calculate control signal
        double control = pid.calculate(current_temp, dt);

        // Update temperature using model
        current_temp = temperatureModel(current_temp, control, dt);

        // Save data
        time_points.push_back(time);
        temperatures.push_back(current_temp);
        control_signals.push_back(control);
        setpoints.push_back(setpoint);

        // Display progress
        if (i % 100 == 0) {
            std::cout << "Time: " << time
                << " sec, Temperature: " << current_temp
                << " °C, Setpoint: " << setpoint
                << " °C, Control: " << control << "%\n";
        }
    }

    // Write data to CSV file
    if (std::ofstream csv_file("temperature_data.csv"); csv_file.is_open()) {
        csv_file << "Time,Temperature,Setpoint,Control_Signal\n";
        for (size_t i = 0; i < time_points.size(); i++) {
            csv_file << time_points[i] << ","
                << temperatures[i] << ","
                << setpoints[i] << ","
                << control_signals[i] << "\n";
        }
        csv_file.close();
        std::cout << "\nData saved to temperature_data.csv\n";
    }
    else {
        std::cerr << "Error creating CSV file!\n";
        return;
    }

    // Output statistics
    std::cout << "\n=== Simulation Statistics ===\n";
    std::cout << "Number of data points: " << time_points.size() << "\n";
    std::cout << "Final temperature: " << temperatures.back() << " °C\n";
    std::cout << "Target temperature: " << setpoint << " °C\n";
    std::cout << "Control error: " << setpoint - temperatures.back() << " °C\n";
}

/**
 * @brief Main program function
 * @return Program exit code
 */
int main() {
    std::cout << "PID Temperature Controller Simulation\n";
    std::cout << "=====================================\n";

    // Default parameters
    double Kp = 2.5, Ki = 0.5, Kd = 1.0;
    double min_output = 0, max_output = 100;
    double initial_temp = 20.0;
    double dt = 0.1;
    int simulation_time = 100;

    PIDController pid(Kp, Ki, Kd, min_output, max_output);

    while (true) {
        int choice = displayMenu();

        switch (choice) {
        case 1: {
            // Run with default temperature (75°C)
            runSimulation(pid, 75.0, initial_temp, dt, simulation_time);
            break;
        }

        case 2: {
            // Get custom temperature from user
            double custom_temp = getTemperatureInput();
            runSimulation(pid, custom_temp, initial_temp, dt, simulation_time);
            break;
        }

        case 3: {
            // Exit
            std::cout << "Exiting program.\n";
            return 0;
        }
        }

        // Ask if user wants to continue
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    return 0;
}