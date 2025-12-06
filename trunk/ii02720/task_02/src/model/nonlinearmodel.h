#pragma once

#include "isimulatedmodel.h"
#include <cmath>
#include <vector>

class NonLinearModel : public ISimulatedModel
{
public:
    NonLinearModel(const double coeffA, const double coeffB, 
                   const double coeffC, const double coeffD)
        : m_coeffA(coeffA), m_coeffB(coeffB), m_coeffC(coeffC), m_coeffD(coeffD) 
    {}
    
    ~NonLinearModel() override = default;

    std::vector<double> simulate(double temp, const double heat, int steps) const override
    {    
        double previousTemp = temp;
        double previousHeat = 0.0;
        
        std::vector<double> temperatureHistory;
        temperatureHistory.reserve(steps + 1);
        
        for(int step = 0; step <= steps; step++)
        {
            temperatureHistory.push_back(temp);
            
            double nextTemp = m_coeffA * temp 
                            - m_coeffB * previousTemp * previousTemp 
                            + m_coeffC * heat 
                            + m_coeffD * std::sin(previousHeat);
            
            previousTemp = temp;
            previousHeat = heat;
            temp = nextTemp;
        }
        
        return temperatureHistory;
    }

private:
    const double m_coeffA;
    const double m_coeffB;
    const double m_coeffC;
    const double m_coeffD;
};
