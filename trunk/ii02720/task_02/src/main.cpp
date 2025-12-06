#include <iostream>

#include "factory/factorylinearmodel.h"
#include "factory/factorynonlinearmodel.h"

int main() 
{
    std::unique_ptr<IFactoryModel> factory;
    std::unique_ptr<ISimulatedModel> model;
    
    const double y = 20.0;
    const double u = 2.0;
    const int t = 10;

    std::cout << "Linear simulation:" << std::endl;
    factory = std::make_unique<FactoryLinearModel>();
    model = factory->getModel();
    auto linear_result = model->simulate(y, u, t);
    for (const auto& value : linear_result) 
    {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl; 
    factory = std::make_unique<FactoryNonLinearModel>();
    model = factory->getModel();
    auto nonlinear_result = model->simulate(y, u, t);
    for (const auto& value : nonlinear_result) 
    {
        std::cout << value << std::endl;
    }

    return 0;
}
