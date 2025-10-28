#include "modelsimulation.h"

void printResults(const std::vector<double>& results, const std::string& modelName) {
    std::cout << modelName << " simulation results:" << std::endl;
    for (size_t i = 0; i < results.size(); i++) {
        std::cout << i << ' ' << results[i] << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    SimulationParams simParams = getDefaultSimulationParams();

    // Get results as vectors
    std::vector<double> linearResults = simulateLinearModel(simParams);
    std::vector<double> nonlinearResults = simulateNonLinearModel(simParams);

    // Print results
    printResults(linearResults, "Linear");
    printResults(nonlinearResults, "NonLinear");

    return 0;
}