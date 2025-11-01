#include <iostream>

#include "factory/factorylinearmodel.hpp"
#include "factory/factorynonlinearmodel.hpp"

#include "adaptivecontroller.hpp"
#include "regulator/pidregulator.hpp"

int main() 
{
    const double w = 10; // Input warm.
    const int t = 10;     // Simulation time steps.
    
    std::cout << "Linear simulation:" << std::endl;
    auto pidRegulatorForLinearModel = std::make_unique<PIDRegulator>();
    auto linearFactory = std::make_unique<FactoryLinearModel>();
    auto linearModel = linearFactory->getDefaultModel();

    auto linearController = std::make_unique<AdaptiveController>(std::move(pidRegulatorForLinearModel), std::move(linearModel)); 
    auto linear_result = linearController->run(w, t);
    for (const auto& value : linear_result) 
    {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;


    std::cout << "Nonlinear simulation:" << std::endl; 
    auto pidRegulatorForNonLinearModel = std::make_unique<PIDRegulator>();
    auto nonlinearFactory = std::make_unique<FactoryNonLinearModel>();
    auto nonlinearModel = nonlinearFactory->getDefaultModel();

    auto nonlinearController = std::make_unique<AdaptiveController>(std::move(pidRegulatorForNonLinearModel), std::move(nonlinearModel)); 
    auto nonlinear_result = nonlinearController->run(w, t);
    for (const auto& value : nonlinear_result) 
    {
        std::cout << value << std::endl;
    }

    return 0;
}