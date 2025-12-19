#pragma once

#include "isimulatedmodel.h"
#include <vector>

class LinearModel : public ISimulatedModel
{
public:
    LinearModel(const double coeffA, const double coeffB)
        : m_coeffA(coeffA), m_coeffB(coeffB) 
    {}
    
    ~LinearModel() override = default;

    std::vector<double> simulate(double temp, const double heat, int steps) const override
    {   
        std::vector<double> temperatureHistory;
        temperatureHistory.reserve(steps + 1);
        
        for(int step = 0; step <= steps; step++)
        {
            temperatureHistory.push_back(temp);
            temp = m_coeffA * temp + m_coeffB * heat;
        }
        
        return temperatureHistory;
    }
    
private:
    const double m_coeffA;
    const double m_coeffB;
};
