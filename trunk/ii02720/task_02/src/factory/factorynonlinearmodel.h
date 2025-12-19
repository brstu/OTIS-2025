#pragma once

#include "ifactorymodel.h"
#include "../model/nonlinearmodel.h"
#include <memory>

class FactoryNonLinearModel : public IFactoryModel
{
public:
    FactoryNonLinearModel() = default;
    ~FactoryNonLinearModel() override = default;

    std::unique_ptr<ISimulatedModel> createModel() const override
    { 
        return std::make_unique<NonLinearModel>(COEFF_A, COEFF_B, COEFF_C, COEFF_D); 
    }

private:
    static constexpr double COEFF_A = 0.8;
    static constexpr double COEFF_B = 0.01;
    static constexpr double COEFF_C = 0.4;
    static constexpr double COEFF_D = 0.1;
};
