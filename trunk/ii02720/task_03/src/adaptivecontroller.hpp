#pragma once
#include "regulator/iregulator.hpp"
#include "model/isimulatedmodel.hpp"
#include <memory>
#include <vector>

class AdaptiveController
{
public:
    AdaptiveController(std::unique_ptr<IRegulator> reg, std::unique_ptr<ISimulatedModel> mod)
        : m_regulator(std::move(reg)), m_model(std::move(mod))
    {}

    std::vector<double> execute(double setpoint, int duration)
    {
        std::vector<double> temps;
        double error = setpoint;
        
        for(int t = 0; t <= duration; ++t)
        {
            double control = m_regulator->compute(error, t);
            double output = m_model->calculate(control);
            temps.push_back(output);
            error = setpoint - output;
        }
        return temps;
    }

private:
    std::unique_ptr<IRegulator> m_regulator;
    std::unique_ptr<ISimulatedModel> m_model; 
};
