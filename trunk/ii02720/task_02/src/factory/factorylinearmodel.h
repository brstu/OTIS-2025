#pragma once

#include "ifactorymodel.h"
#include "../model/linearmodel.h"
#include <memory>

class FactoryLinearModel : public IFactoryModel_2720
{
public:
    FactoryLinearModel() = default;
    ~FactoryLinearModel() override = default;

    std::unique_ptr<ISimulatedModel_2720> getModel() const override
    {
        return std::make_unique<LinearModel>(m_a, m_b, m_initialY);
    }

private:
    const double m_a { 0.8 };        // Coefficient for previous output (y)
    const double m_b { 0.3 };        // Coefficient for input (u)
    const double m_initialY { 20.0 }; // Initial temperature
};