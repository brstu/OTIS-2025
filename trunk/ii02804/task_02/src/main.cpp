#include <iostream>
#include "factory/factorylinearmodel.h"
#include "factory/factorynonlinearmodel.h"

int main() {
    int n;
    double u0, y0;
    std::cout << "Enter number of time steps n: ";
    std::cin >> n;

    std::cout << "Enter initial heat input u0: ";
    std::cin >> u0;

    std::cout << "Enter initial temperature y0: ";
    std::cin >> y0;

    FactoryLinearModel linearFactory;
    FactoryNonlinearModel nonlinearFactory;

    auto linearModel = linearFactory.create();
    auto nonlinearModel = nonlinearFactory.create();

    std::cout << "\n--- Linear Model ---\n";
    auto linResults = linearModel->simulate(n, u0, y0);
    for (int i = 0; i < linResults.size(); ++i)
        std::cout << "Time " << i + 1 << ": " << linResults[i] << std::endl;

    std::vector<double> inputs;
    for (int i = 0; i < n; ++i) {
        double u;
        std::cout << "Enter heat input at time " << i + 1 << ": ";
        std::cin >> u;
        inputs.push_back(u);
    }

    std::cout << "\n--- Nonlinear Model ---\n";
    auto nonlinResults = nonlinearModel->simulate(n, u0, y0, inputs);
    for (int i = 0; i < nonlinResults.size(); ++i)
        std::cout << "Time " << i + 1 << ": " << nonlinResults[i] << std::endl;

    return 0;
}
