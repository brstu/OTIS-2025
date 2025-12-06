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
        return std::make_unique<NonLinearModel>(m_a, m_b, m_c, m_d); 
    }

private:
    const double m_a { 0.8 };  // Linear coefficient for current NonLinearModel's output (y)
    const double m_b { 0.01 }; // Nonlinear coefficient for squared previous NonLinearModel's output (prevY²)
    const double m_c { 0.4 };  // Linear coefficient for NonLinearModel's input (u)
    const double m_d { 0.1 };  // Nonlinear coefficient for sinusoidal NonLinearModel's input term

};

