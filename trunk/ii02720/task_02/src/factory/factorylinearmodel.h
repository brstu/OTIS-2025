#pragma once

#include "ifactorymodel.h"
#include "../model/linearmodel.h"
#include <memory>

class FactoryLinearModel : public IFactoryModel
{
public:
    FactoryLinearModel() = default;
    ~FactoryLinearModel() override = default;

    std::unique_ptr<ISimulatedModel> createModel() const override
    { 
        return std::make_unique<LinearModel>(COEFF_A, COEFF_B); 
    }

private:
    static constexpr double COEFF_A = 0.8;
    static constexpr double COEFF_B = 0.3;
};
