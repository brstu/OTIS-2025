#include "plot_utils.h"
#include <cstdlib>
#include <iostream>

void generatePythonPlotScript() {
    std::cout << "Running Python visualization..." << std::endl;
    system("python3 plot_pid_results.py");
}