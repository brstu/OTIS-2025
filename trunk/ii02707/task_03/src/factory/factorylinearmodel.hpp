#pragma once
#include "ifactorymodel.hpp"
#include "../model/linearmodel.hpp"
#include <memory>

/**
 * @brief Factory class that produces NonLinearModel.
 */
class FactoryLinearModel : public IFactoryModel
{
public:
    /**
     * @brief Default constructor.
     */
    explicit FactoryLinearModel() = default;

    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    ~FactoryLinearModel() override = default;

    /**
     * @brief Creates and returns a default LinearModel.
     *
     * @return A unique pointer to a newly created LinearModel instance.
     */
    std::unique_ptr<ISimulatedModel> getDefaultModel() const override
    { 
        constexpr double DEFAULT_A = 0.5;
        constexpr double DEFAULT_B = 0.5;
        return std::make_unique<LinearModel>(DEFAULT_A, DEFAULT_B); 
    }

};