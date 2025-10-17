#pragma once

#include "ifactorymodel.h"
#include "../model/linearmodel.h"
#include <memory>

class FactoryLinearModel : public IFactoryModel
{
public:
    FactoryLinearModel() = default;
    ~FactoryLinearModel() override = default;

    std::unique_ptr<ISimulatedModel> getModel() const override
    { 
        return std::make_unique<LinearModel>(m_a, m_b); 
    }

private:
    const double m_a { 0.5 }; // Coefficient for previous LinearModel's output (y)
    const double m_b { 0.5 }; // Coefficient for LinearModel's input (u)

};