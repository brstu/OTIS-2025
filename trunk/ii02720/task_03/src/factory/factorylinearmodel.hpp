#pragma once
#include "ifactorymodel.hpp"
#include "../model/linearmodel.hpp"
#include <memory>

class FactoryLinearModel : public IFactoryModel
{
public:
    FactoryLinearModel() = default;
    ~FactoryLinearModel() override = default;

    std::unique_ptr<ISimulatedModel> createModel() const override
    { 
        return std::make_unique<LinearModel>(0.5, 0.5); 
    }
};
