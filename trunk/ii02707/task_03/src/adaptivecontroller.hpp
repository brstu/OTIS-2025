#pragma once
#include "regulator/iregulator.hpp"
#include "model/isimulatedmodel.hpp"
#include <memory>
#include <vector>

/**
 * @brief Class that controlls temperature using Regulator & SimulatedModel.
 */
class AdaptiveController
{
public:
    /**
     * @brief Default constructor for creating AdaptiveController.
     * 
     * @param regulator Copy of IRegulator class.
     * @param model Copy of ISimulatedModel class.
     */
    explicit AdaptiveController(std::unique_ptr<IRegulator> regulator, std::unique_ptr<ISimulatedModel> model)
        : m_regulator(std::move(regulator))
        , m_model(std::move(model))
    {}

    /**
     * @brief Computes a vector of calculated temperatures & returns it according to w & t.
     * 
     * @param w Algorithm of system functioning.
     * @param t Time step at which vector of calculated temperatures is computed.
     * 
     * @return A vector of calculated temperatures.
     */
    std::vector<double> run(const double w, const int t)
    {
        std::vector<double> temperatures;
        double e = w; // e(t) = w(t) - y(t), where y(t) = 0
        for(int i = 0; i <= t; i++)
        {
            double u = m_regulator->step(e, i);
            double y = m_model->step(u);
            temperatures.push_back(y);
            e = w - y; // e(t) = w(t) - y(t)
        }
        return temperatures;
    }

private:
    std::unique_ptr<IRegulator> m_regulator;
    std::unique_ptr<ISimulatedModel> m_model; 

};