#include <iostream>
#include <iomanip>

#include "factory/factorylinearmodel.h"
#include "factory/factorynonlinearmodel.h"

int main() 
{
    constexpr double INITIAL_TEMPERATURE = 20.0;
    constexpr double HEAT_INPUT = 2.0;
    constexpr int SIMULATION_STEPS = 10;

    std::cout << "Linear model simulation:" << std::endl;
    
    auto linearFactory = std::make_unique<FactoryLinearModel>();
    auto linearModel = linearFactory->createModel();
    auto linearResults = linearModel->simulate(INITIAL_TEMPERATURE, HEAT_INPUT, SIMULATION_STEPS);
    
    for (size_t i = 0; i < linearResults.size(); ++i) 
    {
        std::cout << "t=" << i << ": " << std::fixed << std::setprecision(4) 
                  << linearResults[i] << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Nonlinear model simulation:" << std::endl;
    
    auto nonlinearFactory = std::make_unique<FactoryNonLinearModel>();
    auto nonlinearModel = nonlinearFactory->createModel();
    auto nonlinearResults = nonlinearModel->simulate(INITIAL_TEMPERATURE, HEAT_INPUT, SIMULATION_STEPS);
    
    for (size_t i = 0; i < nonlinearResults.size(); ++i) 
    {
        std::cout << "t=" << i << ": " << std::fixed << std::setprecision(4) 
                  << nonlinearResults[i] << std::endl;
    }

    return 0;
}
