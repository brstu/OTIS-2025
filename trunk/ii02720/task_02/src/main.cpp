#include <iostream>
#include <vector>

#include "factory/factorylinearmodel.h"
#include "factory/factorynonlinearmodel.h"

int main() 
{
    std::unique_ptr<IFactoryModel> factory;
    std::unique_ptr<ISimulatedModel> model;
    
    std::vector<double> inputs = {2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.0};

    std::cout << "Linear simulation:" << std::endl;
    factory = std::make_unique<FactoryLinearModel>();
    model = factory->getModel();
    
    std::cout << "Step\tTemperature" << std::endl;
    for (size_t i = 0; i < inputs.size(); i++) 
    {
        auto result = model->simulate(inputs[i]);
        std::cout << i << "\t" << result[0] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl; 
    factory = std::make_unique<FactoryNonLinearModel>();
    model = factory->getModel();
    
    std::cout << "Step\tTemperature" << std::endl;
    for (size_t i = 0; i < inputs.size(); i++) 
    {
        auto result = model->simulate(inputs[i]);
        std::cout << i << "\t" << result[0] << std::endl;
    }

    return 0;
}

