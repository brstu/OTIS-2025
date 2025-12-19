#pragma once
#include "ifactorymodel.hpp"
#include "../model/nonlinearmodel.hpp"
#include <memory>

class FactoryNonLinearModel : public IFactoryModel
{
public:
    FactoryNonLinearModel() = default;
    ~FactoryNonLinearModel() override = default;

    std::unique_ptr<ISimulatedModel> createModel() const override
    { 
        return std::make_unique<NonLinearModel>(0.5, 0.5, 0.5, 0.5); 
    }
};
