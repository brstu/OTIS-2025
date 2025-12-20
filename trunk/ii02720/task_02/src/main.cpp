#include <iostream>
#include <vector>

#include "factory/factorylinearmodel.h"
#include "factory/factorynonlinearmodel.h"

int main() 
{
    std::unique_ptr<IFactoryModel> factry;
    std::unique_ptr<ISimulatedModel> mdl;
    
    std::vector<double> inp = {2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.0};

    std::cout << "Linear simulation:" << std::endl;
    factry = std::make_unique<FactoryLinearModel>();
    mdl = factry->getModel();
    
    std::cout << "Step\tTemperature" << std::endl;
    for (size_t i = 0; i < inp.size(); i++)
    {
        auto result = mdl->simulate(inp[i]);
        std::cout << i << "\t" << result[0] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl; 
    factry = std::make_unique<FactoryNonLinearModel>();
    mdl = factry->getModel();
    
    std::cout << "Step\tTemperature" << std::endl;
    for (size_t i = 0; i < inp.size(); i++)
    {
        auto result = mdl->simulate(inp[i]);
        std::cout << i << "\t" << result[0] << std::endl;
    }

    return 0;
}

