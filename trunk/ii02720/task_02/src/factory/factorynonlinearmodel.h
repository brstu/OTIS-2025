#pragma once

#include "ifactorymodel.h"
#include "../model/nonlinearmodel.h"
#include <memory>

class FactoryNonLinearModel : public IFactoryModel
{
public:
    FactoryNonLinearModel() = default;
    ~FactoryNonLinearModel() override = default;

    std::unique_ptr<ISimulatedModel> getModel() const override
    { 
        return std::make_unique<NonLinearModel>(m_a, m_b, m_c, m_d, m_initialY); 
    }

private:
    const double m_a { 0.8 };        // Linear coefficient for current output
    const double m_b { 0.01 };       // Nonlinear coefficient for squared term
    const double m_c { 0.4 };        // Coefficient for input
    const double m_d { 0.1 };        // Coefficient for sinusoidal term
    const double m_initialY { 20.0 }; // Initial temperature

};

