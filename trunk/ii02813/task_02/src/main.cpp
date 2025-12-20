#include <iostream>

#include "factory/factorylinearmodel.h"
#include "factory/factorynonlinearmodel.h"

int main() 
{
    // Настройки симуляции
    const double INITIAL_STATE = 0;      
    const double CONTROL_SIGNAL = 1;     
    const int SIMULATION_TIME = 25;    
    
    std::unique_ptr<IFactoryModel> modelFactory;
    std::unique_ptr<ISimulatedModel> systemModel;

    std::cout << "Результаты моделирования линейной системы:" << std::endl;
    modelFactory = std::make_unique<FactoryLinearModel>();
    systemModel = modelFactory->getModel();
    
    auto linearSimulationData = systemModel->simulate(
        INITIAL_STATE, CONTROL_SIGNAL, SIMULATION_TIME);
    
    for (const auto& dataPoint : linearSimulationData) 
    {
        std::cout << dataPoint << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Результаты моделирования нелинейной системы:" << std::endl;
    modelFactory = std::make_unique<FactoryNonLinearModel>();
    systemModel = modelFactory->getModel();
    
    auto nonlinearSimulationData = systemModel->simulate(
        INITIAL_STATE, CONTROL_SIGNAL, SIMULATION_TIME);
    

    for (const auto& dataPoint : nonlinearSimulationData) 
    {
        std::cout << dataPoint << std::endl;
    }

    return 0;
}