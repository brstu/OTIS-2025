#include <cstdlib>
#include <iostream>
#include "plot_utils.h"

void generatePythonPlotScript() {
    std::cout << "Running Python visualization script..." << std::endl;
    
    // Проверяем существование CSV файла
    if (system("test -f simulation_results.csv") != 0) {
        std::cerr << "Error: simulation_results.csv not found!" << std::endl;
        std::cerr << "Please run the simulation first." << std::endl;
        return;
    }
    
    // Запускаем Python скрипт
    int result = system("python3 plot_pid_results.py");
    if (result != 0) {
        std::cerr << "Failed to run Python script" << std::endl;
    }
}