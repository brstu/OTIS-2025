#pragma once
#include "isimulatedmodel.hpp"
#include <vector>
#include <cmath>

class NonLinearModel : public ISimulatedModel
{
public:
    NonLinearModel(double a, double b, double c, double d)
        : m_paramA(a), m_paramB(b), m_paramC(c), m_paramD(d),
          m_temp(0.0), m_prevTemp(0.0), m_prevInput(0.0)
    {}

    ~NonLinearModel() override = default;

    double calculate(const double inputWarm) override
    {     
        double newTemp = m_paramA * m_temp 
                       - m_paramB * m_prevTemp * m_prevTemp 
                       + m_paramC * inputWarm 
                       + m_paramD * std::sin(m_prevInput);
        
        m_prevTemp = m_temp;
        m_temp = newTemp;
        m_prevInput = inputWarm;
        
        return newTemp;
    }

    std::vector<double> runSimulation(double initialTemp, const double inputWarm, int steps) override
    {  
        m_prevTemp = initialTemp - 0.001;
        std::vector<double> output;
        
        for(int i = 0; i <= steps; ++i)
        {
            m_prevInput = inputWarm - 1 + i * 0.5;
            output.push_back(initialTemp);
            initialTemp = calculate(inputWarm);
        }
        return output;
    }

private:
    double m_paramA, m_paramB, m_paramC, m_paramD;
    double m_temp, m_prevTemp, m_prevInput;
};
