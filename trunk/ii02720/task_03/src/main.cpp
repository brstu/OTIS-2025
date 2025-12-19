#include <iostream>
#include "factory/factorylinearmodel.hpp"
#include "factory/factorynonlinearmodel.hpp"
#include "adaptivecontroller.hpp"
#include "regulator/pidregulator.hpp"

int main() 
{
    double setpoint = 10.0;
    int duration = 10;
    
    std::cout << "=== Linear Model ===" << std::endl;
    auto linReg = std::make_unique<PIDRegulator>();
    auto linFactory = std::make_unique<FactoryLinearModel>();
    auto linModel = linFactory->createModel();
    auto linController = std::make_unique<AdaptiveController>(std::move(linReg), std::move(linModel)); 
    
    for (auto val : linController->execute(setpoint, duration)) 
        std::cout << val << std::endl;

    std::cout << "\n=== NonLinear Model ===" << std::endl; 
    auto nlReg = std::make_unique<PIDRegulator>();
    auto nlFactory = std::make_unique<FactoryNonLinearModel>();
    auto nlModel = nlFactory->createModel();
    auto nlController = std::make_unique<AdaptiveController>(std::move(nlReg), std::move(nlModel)); 
    
    for (auto val : nlController->execute(setpoint, duration)) 
        std::cout << val << std::endl;

    return 0;
}
