#pragma once
#include "ifactorymodel.hpp"
#include "../model/nonlinearmodel.hpp"
#include <memory>

/**
 * @brief Factory class that produces NonLinearModel.
 */
class FactoryNonLinearModel : public IFactoryModel
{
public:
    /**
     * @brief Default constructor.
     */
    explicit FactoryNonLinearModel() = default;
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    ~FactoryNonLinearModel() override = default;

    /**
     * @brief Creates and returns a default NonLinearModel.
     *
     * @return A unique pointer to a newly created NonLinearModel instance.
     */
    std::unique_ptr<ISimulatedModel> getDefaultModel() const override
    { 
        constexpr double DEFAULT_A = 0.5;
        constexpr double DEFAULT_B = 0.5;
        constexpr double DEFAULT_C = 0.5;
        constexpr double DEFAULT_D = 0.5;
        return std::make_unique<NonLinearModel>(DEFAULT_A, DEFAULT_B, DEFAULT_C, DEFAULT_D); 
    }

};

