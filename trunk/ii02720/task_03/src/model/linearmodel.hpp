#pragma once
#include "isimulatedmodel.hpp"
#include <vector>

class LinearModel : public ISimulatedModel
{
public:
    LinearModel(double coeffA, double coeffB)
        : m_coeffA(coeffA), m_coeffB(coeffB), m_currentTemp(0.0) 
    {}
    
    ~LinearModel() override = default;

    double calculate(const double inputWarm) override
    {   
        m_currentTemp = m_coeffA * m_currentTemp + m_coeffB * inputWarm;
        return m_currentTemp; 
    }

    std::vector<double> runSimulation(double initialTemp, const double inputWarm, int steps) override
    {   
        std::vector<double> output;
        double temp = initialTemp;
        for(int step = 0; step <= steps; ++step)
        {
            output.push_back(temp);
            temp = calculate(inputWarm);
        } 
        return output;
    }
    
private:
    double m_coeffA;
    double m_coeffB;
    double m_currentTemp;
};
